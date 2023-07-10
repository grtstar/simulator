"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class AppRoomProperties(object):
    __slots__ = ["roomId", "cleanOrder", "cleanRepeart", "mopRepeat", "colorOrder", "donotSweep", "donotMop", "fanPower", "waterLevel", "enableYMop"]

    __typenames__ = ["int16_t", "int16_t", "int16_t", "int16_t", "int8_t", "int8_t", "int8_t", "int8_t", "int8_t", "int8_t"]

    __dimensions__ = [None, None, None, None, None, None, None, None, None, None]

    def __init__(self):
        self.roomId = 0
        self.cleanOrder = 0
        self.cleanRepeart = 0
        self.mopRepeat = 0
        self.colorOrder = 0
        self.donotSweep = 0
        self.donotMop = 0
        self.fanPower = 0
        self.waterLevel = 0
        self.enableYMop = 0

    def encode(self):
        buf = BytesIO()
        buf.write(AppRoomProperties._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">hhhhbbbbbb", self.roomId, self.cleanOrder, self.cleanRepeart, self.mopRepeat, self.colorOrder, self.donotSweep, self.donotMop, self.fanPower, self.waterLevel, self.enableYMop))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != AppRoomProperties._get_packed_fingerprint():
            raise ValueError("Decode error")
        return AppRoomProperties._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = AppRoomProperties()
        self.roomId, self.cleanOrder, self.cleanRepeart, self.mopRepeat, self.colorOrder, self.donotSweep, self.donotMop, self.fanPower, self.waterLevel, self.enableYMop = struct.unpack(">hhhhbbbbbb", buf.read(14))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if AppRoomProperties in parents: return 0
        tmphash = (0x2768af6c5c8d518) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if AppRoomProperties._packed_fingerprint is None:
            AppRoomProperties._packed_fingerprint = struct.pack(">Q", AppRoomProperties._get_hash_recursive([]))
        return AppRoomProperties._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", AppRoomProperties._get_packed_fingerprint())[0]

