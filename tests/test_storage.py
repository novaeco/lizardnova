import re


def test_default_config():
    with open('main/storage.cpp') as f:
        content = f.read()
    pattern = r"habitat_config_t g_habitat_config = \{\s*30,\s*50\s*\}"
    assert re.search(pattern, content) is not None
