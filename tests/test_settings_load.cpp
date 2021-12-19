#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <mocks/filesystem_mock.h>

#include "../library/src/logic/load_save_settings.h"
#include "../library/src/utils/json.h"

using namespace ::testing;

namespace
{

const std::string&
sample_of_valid_settings_content ()
{
   static const std::string json = R"(
   {
      "dialog_stylesheet" : "background-color: rgb(46, 52, 54) ",
      "gauge_stylesheet" : "body { color: rgb(179, 179, 0); background-color: rgb(50, 56, 58) } ",
      "gauge_configurations" :
      [  {  "type" : "clock",
            "location" : [0, 0, 1, 1],
            "{format}" : "ddd MMMM d yyyy hh:mm:ss",
            "{timezone}" : "America/Tijuana"
         },
         {  "type" : "webport",
            "location" : [0, 1, 1, 1],
            "{content}" : "<iframe src=\"https://mars.nasa.gov/layout/embed/image/320mosaicvert/?i=N_L000_0621XEDR031POLTSB1330_DRIVEM1\" width=\"320\" height=\"320\" scrolling=\"no\" frameborder=\"0\"></iframe>"
         },
         {  "type" : "twitter",
            "location" : [0, 2, 2, 1],
            "{handle}" : "NASAPersevere"
         },
         {  "type" : "webport",
            "location" : [1, 1, 1, 1],
            "{content}" : "<h1>Hello 🍌🐒<h1>"
         }
      ]
   })";

   return json;
}

}

TEST(settings_load, will_use_system_config_folder)
{
   // arrange
   std::filesystem::path path = "/config/folder123";
   std::filesystem::path config_file = path / "settings.json";
   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));

   // assert
   EXPECT_CALL(fs_mock, exists(config_file));

   // act
   auto __ = logic::load_settings(fs_mock);
}

TEST(settings_load, will_not_attempt_reading_file_if_not_exists)
{
   // arrange
   std::filesystem::path path = "/config/folder234";
   std::filesystem::path config_file = path / "settings.json";
   StrictMock<filesystem_mock> fs_mock; // to cover all variants of reading a file
   EXPECT_CALL(fs_mock, get_system_app_config_location()).WillRepeatedly(Return(path));

   // assert
   EXPECT_CALL(fs_mock, exists(config_file)).WillRepeatedly(Return(false));
   // + didn't call any other filesystem functions (it's a strict mock)

   // act
   auto __ = logic::load_settings(fs_mock);
}

TEST(settings_load, will_not_attempt_reading_file_if_not_regular)
{
   // arrange
   std::filesystem::path path = "/config/folder3454";
   std::filesystem::path config_file = path / "settings.json";
   StrictMock<filesystem_mock> fs_mock; // to cover all variants of reading a file
   EXPECT_CALL(fs_mock, get_system_app_config_location()).WillRepeatedly(Return(path));

   // assert
   EXPECT_CALL(fs_mock, exists(config_file)).WillRepeatedly(Return(true));
   EXPECT_CALL(fs_mock, is_regular_file(config_file)).WillRepeatedly(Return(false));
   // + didn't call any other filesystem functions (it's a strict mock)

   // act
   auto __ = logic::load_settings(fs_mock);
}

TEST(settings_load, will_read_the_correct_file)
{
   // arrange
   std::filesystem::path path = "/config/folder4556";
   std::filesystem::path config_file = path / "settings.json";
   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));
   ON_CALL(fs_mock, exists(config_file)).WillByDefault(Return(true));
   ON_CALL(fs_mock, is_regular_file(config_file)).WillByDefault(Return(true));

   // assert
   EXPECT_CALL(fs_mock, read_file(config_file));

   // act
   auto __ = logic::load_settings(fs_mock);
}

TEST(settings_load, will_deserialise_entire_contents_of_the_file)
{
   // arrange
   std::filesystem::path path = "/config/folder5667";
   std::filesystem::path config_file = path / "settings.json";
   std::string file_content = sample_of_valid_settings_content ();
   const int num_gauges_in_sample = 4;

   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));
   ON_CALL(fs_mock, exists(config_file)).WillByDefault(Return(true));
   ON_CALL(fs_mock, is_regular_file(config_file)).WillByDefault(Return(true));
   ON_CALL(fs_mock, read_file(config_file)).WillByDefault(Return(file_content));

   // act
   auto sett = logic::load_settings(fs_mock);

   // assert
   ASSERT_EQ(num_gauges_in_sample, sett.gauge_configurations.size());
}

TEST(settings_load, will_correctly_handle_utf8_chars)
{
   // arrange
   std::filesystem::path path = "/config/folder6778";
   std::filesystem::path config_file = path / "settings.json";
   std::string file_content = sample_of_valid_settings_content ();
   std::wstring utf8_content_in_sample = L"<h1>Hello 🍌🐒<h1>";

   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));
   ON_CALL(fs_mock, exists(config_file)).WillByDefault(Return(true));
   ON_CALL(fs_mock, is_regular_file(config_file)).WillByDefault(Return(true));
   ON_CALL(fs_mock, read_file(config_file)).WillByDefault(Return(file_content));

   // act
   auto sett = logic::load_settings(fs_mock);

   // assert
   ASSERT_EQ(utf8_content_in_sample, sett.gauge_configurations[3].settings[0].value);
}

TEST(settings_load, will_use_default_settings_if_file_doesnt_exist)
{
   // arrange
   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, exists(_)).WillByDefault(Return(false));

   // act
   auto settings_loaded = logic::load_settings(fs_mock);
   auto settings_expected = utils::deserialise_settings(logic::default_settings_content());

   // assert
   ASSERT_EQ(settings_expected.dialog_stylesheet, settings_loaded.dialog_stylesheet);
   ASSERT_EQ(settings_expected.gauge_stylesheet, settings_loaded.gauge_stylesheet);
   ASSERT_EQ(settings_expected.gauge_configurations.size(), settings_loaded.gauge_configurations.size());
   ASSERT_EQ(settings_expected.gauge_configurations[2].settings[0].value, settings_loaded.gauge_configurations[2].settings[0].value);
}

TEST(settings_load, will_use_default_settings_if_file_empty)
{
   // arrange
   std::filesystem::path path = "/config/folder5667";
   std::filesystem::path config_file = path / "settings.json";

   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));
   ON_CALL(fs_mock, exists(config_file)).WillByDefault(Return(true));
   ON_CALL(fs_mock, is_regular_file(config_file)).WillByDefault(Return(true));
   ON_CALL(fs_mock, read_file(config_file)).WillByDefault(Return(""));

   // act
   auto settings_loaded = logic::load_settings(fs_mock);
   auto settings_expected = utils::deserialise_settings(logic::default_settings_content());

   // assert
   ASSERT_EQ(settings_expected.dialog_stylesheet, settings_loaded.dialog_stylesheet);
   ASSERT_EQ(settings_expected.gauge_stylesheet, settings_loaded.gauge_stylesheet);
   ASSERT_EQ(settings_expected.gauge_configurations.size(), settings_loaded.gauge_configurations.size());
   ASSERT_EQ(settings_expected.gauge_configurations[2].settings[0].value, settings_loaded.gauge_configurations[2].settings[0].value);
}
