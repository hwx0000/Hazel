#pragma once

namespace Hazel
{
	class TextureLoader
	{
	public:
		static unsigned char* Load(const char* path, bool inverse, int& width, int& height, int& nrChannels);
		static void Free(void* data);
	};
}