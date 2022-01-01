#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../library/src/utils/json.h"

namespace
{

logic::settings
get_sample_settings ()
{
   logic::settings settings;

   settings.gauge_stylesheet = "gauge stylesheets 1";
   settings.dialog_stylesheet = "dialog stylesheets 2";

   std::map<std::string, std::string> gauge1_settings {
      {"tag1", "value1"},
      {"tag12", "value12"}};
   gauge::configuration gauge1_configuration {
      .type = gauge::type::twitter,
      .location = gauge::location{1, 2, 3, 4},
      .settings = gauge1_settings};
   settings.gauge_configurations.push_back(gauge1_configuration);

   std::map<std::string, std::string> gauge2_settings{
      {"tag123", "value123"},
      {"tag1234", "value1234"}};
   gauge::configuration gauge2_configuration{
      .type = gauge::type::clock,
      .location = gauge::location{5, 6, 7, 8},
      .settings = gauge2_settings};
   settings.gauge_configurations.push_back(gauge2_configuration);

   return settings;
}

}

TEST(settings_serialisation, gauge_stylesheet)
{
   // arrange
   logic::settings settings_in = get_sample_settings ();
   // act
   auto serialised = utils::serialise_settings(settings_in);
   logic::settings settings_out = utils::deserialise_settings(serialised);
   // assert
   EXPECT_EQ(settings_in.gauge_stylesheet, settings_out.gauge_stylesheet);
}

TEST(settings_serialisation, dialog_stylesheet)
{
   // arrange
   logic::settings settings_in = get_sample_settings ();
   // act
   auto serialised = utils::serialise_settings(settings_in);
   logic::settings settings_out = utils::deserialise_settings(serialised);
   // assert
   EXPECT_EQ(settings_in.dialog_stylesheet, settings_out.dialog_stylesheet);
}

TEST(settings_serialisation, configurations_empty)
{
   // arrange
   logic::settings settings_in;
   // act
   auto serialised = utils::serialise_settings(settings_in);
   logic::settings settings_out = utils::deserialise_settings(serialised);
   // assert
   EXPECT_TRUE(settings_out.gauge_configurations.empty());
}

TEST(settings_serialisation, configurations_same_count)
{
   // arrange
   logic::settings settings_in = get_sample_settings ();
   // act
   auto serialised = utils::serialise_settings(settings_in);
   logic::settings settings_out = utils::deserialise_settings(serialised);
   // assert
   EXPECT_EQ(settings_in.gauge_configurations.size(), settings_out.gauge_configurations.size());
}

TEST(settings_serialisation, configurations_types)
{
   // arrange
   logic::settings settings_in = get_sample_settings ();
   // act
   auto serialised = utils::serialise_settings(settings_in);
   logic::settings settings_out = utils::deserialise_settings(serialised);
   // assert
   EXPECT_EQ(settings_in.gauge_configurations[0].type, settings_out.gauge_configurations[0].type);
   EXPECT_EQ(settings_in.gauge_configurations[1].type, settings_out.gauge_configurations[1].type);
}

TEST(settings_serialisation, configurations_settings)
{
   // arrange
   logic::settings settings_in = get_sample_settings ();
   // act
   auto serialised = utils::serialise_settings(settings_in);
   logic::settings settings_out = utils::deserialise_settings(serialised);
   // assert
   for(std::size_t i : {std::size_t(0), std::size_t(1)})
   {
      EXPECT_TRUE(std::equal(
         settings_in.gauge_configurations[i].settings.begin(), settings_in.gauge_configurations[i].settings.end(),
         settings_out.gauge_configurations[i].settings.begin(), settings_out.gauge_configurations[i].settings.end()
      ));
   }
}

TEST(settings_serialisation, configurations_locations)
{
   // arrange
   logic::settings settings_in = get_sample_settings ();
   // act
   auto serialised = utils::serialise_settings(settings_in);
   logic::settings settings_out = utils::deserialise_settings(serialised);
   // assert
   EXPECT_EQ(settings_in.gauge_configurations[0].location.y, settings_out.gauge_configurations[0].location.y);
   EXPECT_EQ(settings_in.gauge_configurations[0].location.x, settings_out.gauge_configurations[0].location.x);
   EXPECT_EQ(settings_in.gauge_configurations[0].location.height, settings_out.gauge_configurations[0].location.height);
   EXPECT_EQ(settings_in.gauge_configurations[0].location.width, settings_out.gauge_configurations[0].location.width);
   EXPECT_EQ(settings_in.gauge_configurations[1].location.y, settings_out.gauge_configurations[1].location.y);
   EXPECT_EQ(settings_in.gauge_configurations[1].location.x, settings_out.gauge_configurations[1].location.x);
   EXPECT_EQ(settings_in.gauge_configurations[1].location.height, settings_out.gauge_configurations[1].location.height);
   EXPECT_EQ(settings_in.gauge_configurations[1].location.width, settings_out.gauge_configurations[1].location.width);
}
