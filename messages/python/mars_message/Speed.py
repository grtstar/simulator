"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class Speed(object):
    __slots__ = ["linear", "angular"]

    __typenames__ = ["float", "float"]

    __dimensions__ = [None, None]

    def __init__(self):
        self.linear = 0.0
        self.angular = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(Speed._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">ff", self.linear, self.angular))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != Speed._get_packed_fingerprint():
            raise ValueError("Decode error")
        return Speed._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = Speed()
        self.linear, self.angular = struct.unpack(">ff", buf.read(8))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if Speed in parents: return 0
        tmphash = (0x648c02a374925e5b) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if Speed._packed_fingerprint is None:
            Speed._packed_fingerprint = struct.pack(">Q", Speed._get_hash_recursive([]))
        return Speed._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", Speed._get_packed_fingerprint())[0]

