"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class Quaternion(object):
    __slots__ = ["w", "x", "y", "z"]

    __typenames__ = ["double", "double", "double", "double"]

    __dimensions__ = [None, None, None, None]

    def __init__(self):
        self.w = 0.0
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(Quaternion._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">dddd", self.w, self.x, self.y, self.z))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != Quaternion._get_packed_fingerprint():
            raise ValueError("Decode error")
        return Quaternion._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = Quaternion()
        self.w, self.x, self.y, self.z = struct.unpack(">dddd", buf.read(32))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if Quaternion in parents: return 0
        tmphash = (0x9b2deea5fc88050f) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if Quaternion._packed_fingerprint is None:
            Quaternion._packed_fingerprint = struct.pack(">Q", Quaternion._get_hash_recursive([]))
        return Quaternion._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", Quaternion._get_packed_fingerprint())[0]

