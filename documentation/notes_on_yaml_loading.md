## Be sure to add an extra blank line to the end if it's not present:

```
      if (source_yaml.empty()) return {};
      else if (source_yaml.back() != '\n') source_yaml.append("\n");
```


## Check for known and expected failures when loading

```
TEST(Hexagon__LayoutFromYAMLTest, load__with_invalid_yaml_has_some_predictable_behavior)
{
   std::string invalid_source_yaml = "{# ke\ny{:";
   Hexagon::LayoutFromYAML layout_from_yaml(invalid_source_yaml);
   std::string expected_error_message = "Hexagon::LayoutFromYAML::load() error: YAML::Load failed " \
                                        "to parse and threw the following error message: \"yaml-cpp: " \
                                        "error at line 2, column 2: end of map flow not found\"";
   ASSERT_THROW_WITH_MESSAGE(layout_from_yaml.load(), std::runtime_error, expected_error_message);
}
```

