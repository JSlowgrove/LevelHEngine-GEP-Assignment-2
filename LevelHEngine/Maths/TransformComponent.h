#pragma once

#include "../Core/Component.h"

namespace Maths
{

	class TransformComponent : public Core::Component
	{

	public:
		virtual ~TransformComponent();

		virtual void onAwake();
		virtual void onUpdate();
		virtual void onDestroy();

	private:
		float x;
		float y;
		float z;

		void awake();
		void update();
		void destroy();
	};

}