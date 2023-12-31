"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class BlueToothInfo(object):
    __slots__ = ["timestampMs", "backpile"]

    __typenames__ = ["int64_t", "boolean"]

    __dimensions__ = [None, None]

    def __init__(self):
        self.timestampMs = 0
        self.backpile = False

    def encode(self):
        buf = BytesIO()
        buf.write(BlueToothInfo._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qb", self.timestampMs, self.backpile))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != BlueToothInfo._get_packed_fingerprint():
            raise ValueError("Decode error")
        return BlueToothInfo._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = BlueToothInfo()
        self.timestampMs = struct.unpack(">q", buf.read(8))[0]
        self.backpile = bool(struct.unpack('b', buf.read(1))[0])
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if BlueToothInfo in parents: return 0
        tmphash = (0x40c29ec9290efb05) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if BlueToothInfo._packed_fingerprint is None:
            BlueToothInfo._packed_fingerprint = struct.pack(">Q", BlueToothInfo._get_hash_recursive([]))
        return BlueToothInfo._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", BlueToothInfo._get_packed_fingerprint())[0]

