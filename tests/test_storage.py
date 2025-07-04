class FakeNVS(dict):
    """Simple mock of the NVS key-value storage."""
    def commit(self):
        pass

g_habitat_config = {
    "target_temp": 30,
    "target_humidity": 50,
}

def load_config(nvs):
    temp = g_habitat_config["target_temp"]
    hum = g_habitat_config["target_humidity"]
    temp = nvs.get("temp", temp)
    hum = nvs.get("hum", hum)
    g_habitat_config["target_temp"] = temp
    g_habitat_config["target_humidity"] = hum


def save_config(nvs):
    nvs["temp"] = g_habitat_config["target_temp"]
    nvs["hum"] = g_habitat_config["target_humidity"]
    nvs.commit()


def test_load_save_roundtrip():
    nvs = FakeNVS()
    load_config(nvs)
    assert g_habitat_config["target_temp"] == 30
    assert g_habitat_config["target_humidity"] == 50

    g_habitat_config["target_temp"] = 22
    g_habitat_config["target_humidity"] = 40
    save_config(nvs)

    g_habitat_config["target_temp"] = 0
    g_habitat_config["target_humidity"] = 0
    load_config(nvs)
    assert g_habitat_config["target_temp"] == 22
    assert g_habitat_config["target_humidity"] == 40
