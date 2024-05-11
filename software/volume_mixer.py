from ctypes import cast, POINTER
import serial
import yaml
from comtypes import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume, ISimpleAudioVolume


def read_config(config_file: str) -> dict:
    with open(config_file, 'r') as f:
        conf = yaml.safe_load(f)

    return conf


def read_serial_port(ser_device: serial.Serial(), val_num: int) -> list:
    ser_device.open()
    ser_device.readline()

    serial_values = []

    for i in range(val_num):
        serial_values.append(int.from_bytes(ser_device.read(1)))

    ser_device.close()

    return serial_values


def list_volumes():
    sessions = AudioUtilities.GetAllSessions()

    for session in sessions:
        if session.Process:
            print(session.Process.name())


def change_app_volume(app_name: str, volume: float) -> None:
    if app_name == 'master':
        sound_device = AudioUtilities.GetSpeakers()
        interface = sound_device.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
        handler = cast(interface, POINTER(IAudioEndpointVolume))

        handler.SetMasterVolumeLevelScalar(volume, None)
    else:
        sessions = AudioUtilities.GetAllSessions()

        for session in sessions:
            handler = session._ctl.QueryInterface(ISimpleAudioVolume)

            if type(app_name) is list:
                for app in app_name:
                    if session.Process and session.Process.name() == app:
                        handler.SetMasterVolume(volume, None)
            elif session.Process and session.Process.name() == app_name:
                handler.SetMasterVolume(volume, None)


if __name__ == '__main__':
    config = read_config('C:\\Users\\admin\\My_stuff\\Projects\\volume_mixer\\config.yaml')
    ser = serial.Serial(port=config['serial_port'], baudrate=config['baud_rate'], timeout=None)
    ser.close()

    while (True):
        ser_values = read_serial_port(ser, 5)

        for k, v in config['pot_map'].items():
            change_app_volume(v, ser_values[k] / 100)
