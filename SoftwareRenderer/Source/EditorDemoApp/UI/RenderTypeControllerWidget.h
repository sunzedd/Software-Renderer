#pragma once
#include "ObjectPickerWidgetBase.h"

namespace Demo
{
	class RenderTypeControllerWidget : public ObjectPickerWidgetBase
	{
	public:
		RenderTypeControllerWidget(Scene& scene);

		void render() override;
		void update(unsigned int dtime) override;

	private:

	};
}