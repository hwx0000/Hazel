#pragma once
#include "Hazel.h"
#include "entt.hpp"
#include "GameObject.h"
#include "Components/Component.h"
#include "entt.hpp"

namespace Hazel
{
	class GameObject;
	class Scene;
    class SceneManager
    {
    public:
        SceneManager(const SceneManager& obj) = delete;
        
        static SceneManager* Instance()
        {
            if (s_InstancePtr == NULL)
            {
                s_InstancePtr = new SceneManager();
                return s_InstancePtr;
            }
            else
            {
                return s_InstancePtr;
            }
        }

        std::shared_ptr<Scene> CopyScene(const Scene& src);

        // Copy component from one Entity to another Enity in new register
        template<class T>
        void CopyComponentForGameObjectIfExists(entt::registry& dstRegister, const entt::entity& dstEntity, const entt::registry& srcRegister, const entt::entity& srcEntity,
            const entt::id_type& componentType)
        {
            if (componentType == entt::type_id<T>().hash())
            {
                HAZEL_ASSERT(srcRegister.all_of<T>(srcEntity), "Error in CopyComponentForGameObjectIfExists")

                const T& component = srcRegister.get<T>(srcEntity);
                dstRegister.emplace_or_replace<T>(dstEntity, component);
            }
        }

    private:
        SceneManager() {}

        static SceneManager* s_InstancePtr;
    };
}