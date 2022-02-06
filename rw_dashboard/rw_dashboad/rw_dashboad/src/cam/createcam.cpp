#include "createcam.h"
#include "imgui\imgui.h"

void showcreatecam()
{
	ImGui::Begin("Create Cam");
	//find which available cameras there are from a main data thread

    const char* cameras[] = { "Cam1", "Cam2" };
    static const char* current_cam = NULL;

    if (ImGui::BeginCombo("Camera", current_cam)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(cameras); n++)
        {
            bool is_selected = (current_cam == cameras[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(cameras[n], is_selected))
                current_cam = cameras[n];
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    const char* resolutions[] = { "360p", "720p" };
    static const char* current_res = NULL;

    if (ImGui::BeginCombo("Resolution", current_res)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(resolutions); n++)
        {
            bool is_selected = (current_res == resolutions[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(resolutions[n], is_selected))
                current_res = resolutions[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    if (current_cam != NULL && current_res != NULL)
    {
        if (ImGui::Button("Create Cam"))
        {
            //do something that creates a new window instance
        }
    }

	ImGui::End();
}