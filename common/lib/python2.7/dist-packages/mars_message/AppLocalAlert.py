"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import mars_message.TimedTaskInfo

class AppLocalAlert(object):
    __slots__ = ["verison", "timeZone", "number", "timedTaskInfo"]

    __typenames__ = ["int8_t", "int8_t", "int8_t", "mars_message.TimedTaskInfo"]

    __dimensions__ = [None, None, None, ["number"]]

    def __init__(self):
        self.verison = 0
        self.timeZone = 0
        self.number = 0
        self.timedTaskInfo = []

    def encode(self):
        buf = BytesIO()
        buf.write(AppLocalAlert._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">bbb", self.verison, self.timeZone, self.number))
        for i0 in range(self.number):
            assert self.timedTaskInfo[i0]._get_packed_fingerprint() == mars_message.TimedTaskInfo._get_packed_fingerprint()
            self.timedTaskInfo[i0]._encode_one(buf)

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != AppLocalAlert._get_packed_fingerprint():
            raise ValueError("Decode error")
        return AppLocalAlert._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = AppLocalAlert()
        self.verison, self.timeZone, self.number = struct.unpack(">bbb", buf.read(3))
        self.timedTaskInfo = []
        for i0 in range(self.number):
            self.timedTaskInfo.append(mars_message.TimedTaskInfo._decode_one(buf))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if AppLocalAlert in parents: return 0
        newparents = parents + [AppLocalAlert]
        tmphash = (0xafac23d82e408406+ mars_message.TimedTaskInfo._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if AppLocalAlert._packed_fingerprint is None:
            AppLocalAlert._packed_fingerprint = struct.pack(">Q", AppLocalAlert._get_hash_recursive([]))
        return AppLocalAlert._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", AppLocalAlert._get_packed_fingerprint())[0]

