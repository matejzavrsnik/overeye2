#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "testing_tools.h"

#include "../library/src/logic/load_save_settings.h"
#include "../library/src/utils/json.h"

#include <mocks/filesystem_mock.h>

using namespace ::testing;

TEST(settings_save, will_check_for_existence_of_config_folder)
{
   // arrange
   auto settings_model = utils::deserialise_settings(testing_tools::sample_of_valid_settings_content());

   std::filesystem::path path = "/config/folder/" + testing_tools::get_random_short_string();
   //std::filesystem::path config_file = path / "settings.json";
   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));

   // assert
   EXPECT_CALL(fs_mock, exists(path));

   // act
   logic::save_settings(settings_model, fs_mock);
}

TEST(settings_save, will_check_for_existence_of_system_config_folder)
{
   // arrange
   auto settings_model = utils::deserialise_settings(testing_tools::sample_of_valid_settings_content());

   std::filesystem::path path = "/config/folder/" + testing_tools::get_random_short_string();
   //std::filesystem::path config_file = path / "settings.json";
   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));

   // assert
   EXPECT_CALL(fs_mock, exists(path));

   // act
   logic::save_settings(settings_model, fs_mock);
}

TEST(settings_save, if_config_folder_doesnt_exist_it_will_create_one)
{
   // arrange
   auto settings_model = utils::deserialise_settings(testing_tools::sample_of_valid_settings_content());

   std::filesystem::path path = "/config/folder/" + testing_tools::get_random_short_string();
   //std::filesystem::path config_file = path / "settings.json";
   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));
   ON_CALL(fs_mock, exists(path)).WillByDefault(Return(false));

   // assert
   EXPECT_CALL(fs_mock, create_directories(path));

   // act
   logic::save_settings(settings_model, fs_mock);
}

TEST(settings_save, if_config_folder_exists_it_will_not_attempt_to_create_one)
{
   // arrange
   auto settings_model = utils::deserialise_settings(testing_tools::sample_of_valid_settings_content());

   std::filesystem::path path = "/config/folder/" + testing_tools::get_random_short_string();
   //std::filesystem::path config_file = path / "settings.json";
   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));
   ON_CALL(fs_mock, exists(path)).WillByDefault(Return(true));

   // assert
   EXPECT_CALL(fs_mock, create_directories(path)).Times(0);

   // act
   logic::save_settings(settings_model, fs_mock);
}

TEST(settings_save, will_write_settings_to_file)
{
   // arrange
   auto settings_model = utils::deserialise_settings(testing_tools::sample_of_valid_settings_content());
   auto serialised_settings = utils::serialise_settings(settings_model);

   std::filesystem::path path = "/config/folder/" + testing_tools::get_random_short_string();
   std::filesystem::path config_file = path / "settings.json";
   NiceMock<filesystem_mock> fs_mock;
   ON_CALL(fs_mock, get_system_app_config_location()).WillByDefault(Return(path));
   ON_CALL(fs_mock, exists(path)).WillByDefault(Return(true));

   // assert
   EXPECT_CALL(fs_mock, save_file(config_file, serialised_settings));

   // act
   logic::save_settings(settings_model, fs_mock);
}
