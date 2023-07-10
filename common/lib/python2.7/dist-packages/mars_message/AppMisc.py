"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class AppMisc(object):
    __slots__ = ["verison", "enableNotDisturbTime", "volume", "enableContinueClean", "language", "dustCollctionNum", "enbaleCustomizeMode", "unitSet", "carpetCleanPrefer", "enableAutoBoost", "enableChildLock"]

    __typenames__ = ["int8_t", "int8_t", "int8_t", "int8_t", "int8_t", "int8_t", "int8_t", "int8_t", "int8_t", "int8_t", "int8_t"]

    __dimensions__ = [None, None, None, None, None, None, None, None, None, None, None]

    def __init__(self):
        self.verison = 0
        self.enableNotDisturbTime = 0
        self.volume = 0
        self.enableContinueClean = 0
        self.language = 0
        self.dustCollctionNum = 0
        self.enbaleCustomizeMode = 0
        self.unitSet = 0
        self.carpetCleanPrefer = 0
        self.enableAutoBoost = 0
        self.enableChildLock = 0

    def encode(self):
        buf = BytesIO()
        buf.write(AppMisc._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">bbbbbbbbbbb", self.verison, self.enableNotDisturbTime, self.volume, self.enableContinueClean, self.language, self.dustCollctionNum, self.enbaleCustomizeMode, self.unitSet, self.carpetCleanPrefer, self.enableAutoBoost, self.enableChildLock))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != AppMisc._get_packed_fingerprint():
            raise ValueError("Decode error")
        return AppMisc._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = AppMisc()
        self.verison, self.enableNotDisturbTime, self.volume, self.enableContinueClean, self.language, self.dustCollctionNum, self.enbaleCustomizeMode, self.unitSet, self.carpetCleanPrefer, self.enableAutoBoost, self.enableChildLock = struct.unpack(">bbbbbbbbbbb", buf.read(11))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if AppMisc in parents: return 0
        tmphash = (0x31577f9534314bd) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if AppMisc._packed_fingerprint is None:
            AppMisc._packed_fingerprint = struct.pack(">Q", AppMisc._get_hash_recursive([]))
        return AppMisc._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", AppMisc._get_packed_fingerprint())[0]

