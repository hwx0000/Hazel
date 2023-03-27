# os代表操作系统, 为了让脚本能与os打交道, 这里相当于创建了一个OS模块的对象os
import os
# 创建subprocess模块对象, 可以调用其他的exe
import subprocess

#  =============================  1.Check Python environment  ======================================
# The pkg_resources module provides runtime facilities for finding, introspecting, activating and using installed Python distributions. 
import pkg_resources

def install(package):
    print(f"Installing {package} module...")
    subprocess.check_call(['python', '-m', 'pip', 'install', package])

def ValidatePackage(package):
    required = { package }
    installed = {pkg.key for pkg in pkg_resources.working_set}
    missing = required - installed

	# 安装缺失的package
    if missing:
        install(package)

def ValidatePackages():
    ValidatePackage('requests')
    ValidatePackage('fake-useragent')

# Make sure everything we need is installed, 调用它的ValidatePackage函数
# 这里是保证python环境是完整的
ValidatePackages()

#  =============================  2.define Utils function  ======================================
import requests
import sys
import time

from fake_useragent import UserAgent

# 创建一个帮助显示下载进度的函数
def DownloadFile(url, filepath):
    with open(filepath, 'wb') as f:
        ua = UserAgent()
        headers = {'User-Agent': ua.chrome}
        response = requests.get(url, headers=headers, stream=True)
        total = response.headers.get('content-length')

        if total is None:
            f.write(response.content)
        else:
            downloaded = 0
            total = int(total)
            startTime = time.time()
            for data in response.iter_content(chunk_size=max(int(total/1000), 1024*1024)):
                downloaded += len(data)
                f.write(data)
                done = int(50*downloaded/total)
                percentage = (downloaded / total) * 100
                elapsedTime = time.time() - startTime
                avgKBPerSecond = (downloaded / 1024) / elapsedTime
                avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSecond)
                if (avgKBPerSecond > 1024):
                    avgMBPerSecond = avgKBPerSecond / 1024
                    avgSpeedString = '{:.2f} MB/s'.format(avgMBPerSecond)
                sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format('█' * done, '.' * (50-done), percentage, avgSpeedString))
                sys.stdout.flush()
    sys.stdout.write('\n')

def YesOrNo():
    while True:
        reply = str(input('[Y/N]: ')).lower().strip()
        if reply[:1] == 'y':
            return True
        if reply[:1] == 'n':
            return False

#  =============================  3.Check Vulkan SDK environment  ======================================
# Vulkan是在Setup.py相同路径下的Vulkan.py文件
from pathlib import Path
from io import BytesIO
# urllib.requests是python提供打开和读取URL的库
from urllib.request import Request, urlopen
from zipfile import ZipFile

# VULKAN_SDK代表系统环境变量里存的VULKAN_SDK的版本
VULKAN_SDK = os.environ.get('VULKAN_SDK')
# 官网上下载的url路径
VULKAN_SDK_INSTALLER_URL = 'https://sdk.lunarg.com/sdk/download/1.3.216.0/windows/vulkan_sdk.exe'
HAZEL_VULKAN_VERSION = '1.3.216.0'
# 下载到本地的相对路径
VULKAN_SDK_EXE_PATH = 'Hazel/vendor/VulkanSDK/VulkanSDK.exe'

# 核心的安装SDK的函数
def InstallVulkanSDK():
    print('Downloading {} to {}'.format(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH))
    DownloadFile(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH)
    print("Done!")
    print("Running Vulkan SDK installer...")
    os.startfile(os.path.abspath(VULKAN_SDK_EXE_PATH))
    print("Re-run this script after installation")

# 当SDK未被安装, 或版本不对时, 调用此函数, 进而调用InstallVulkanSDK
def InstallVulkanPrompt():
    print("Would you like to install the Vulkan SDK?")
    install = YesOrNo()
    if (install):
        InstallVulkanSDK()
        quit()

# 检查Vulkan SDK是否被安装
def CheckVulkanSDK():
    if (VULKAN_SDK is None):
        print("You don't have the Vulkan SDK installed!")
        InstallVulkanPrompt()
        return False
    # 目前所用的sdk版本是1.2.170.0
    elif (HAZEL_VULKAN_VERSION not in VULKAN_SDK):
        print(f"Located Vulkan SDK at {VULKAN_SDK}")
        print(f"You don't have the correct Vulkan SDK version! (Hazel requires {HAZEL_VULKAN_VERSION})")
        # 调用此文件内的InstallVulkanPrompt函数, 可以在命令行安装Vulkan SDK
        InstallVulkanPrompt()
        return False
    
    print(f"Correct Vulkan SDK located at {VULKAN_SDK}")
    return True


# 调用CheckVulkanSDK函数
if (not CheckVulkanSDK()):
    print("Vulkan SDK not installed.")
    
#  =============================  4.Call premake5.exe to build solution  ======================================
print("Running premake...")
subprocess.call(["vendor/bin/premake/premake5.exe", "vs2022"])