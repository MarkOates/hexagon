
#include <gtest/gtest.h>

#include <Hexagon/System/Action/OpenDocumentationInBrowser.hpp>

TEST(Hexagon_System_Action_OpenDocumentationInBrowserTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::OpenDocumentationInBrowser open_documentation_in_browser;
}

TEST(Hexagon_System_Action_OpenDocumentationInBrowserTest, execute__returns_the_expected_response)
{
   Hexagon::System::Action::OpenDocumentationInBrowser open_documentation_in_browser;
   open_documentation_in_browser.execute();
}
