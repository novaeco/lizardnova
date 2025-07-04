def temp_from_raw(raw):
    return ((raw & 0xFFFC) / 65535.0) * 175.72 - 46.85

def hum_from_raw(raw):
    return ((raw & 0xFFFC) / 65535.0) * 125 - 6

def test_temperature_conversion():
    assert abs(temp_from_raw(0x68AC) - 25.0) < 0.1
    assert abs(temp_from_raw(0) + 46.85) < 1e-2

def test_humidity_conversion():
    assert abs(hum_from_raw(0x72AC) - 50.0) < 0.1
    assert abs(hum_from_raw(0) + 6.0) < 1e-2
