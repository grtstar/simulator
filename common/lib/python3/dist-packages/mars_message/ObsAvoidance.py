"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class ObsAvoidance(object):
    __slots__ = ["timestampMs", "count", "angles", "ranges"]

    __typenames__ = ["int64_t", "int32_t", "double", "double"]

    __dimensions__ = [None, None, ["count"], ["count"]]

    def __init__(self):
        self.timestampMs = 0
        self.count = 0
        self.angles = []
        self.ranges = []

    def encode(self):
        buf = BytesIO()
        buf.write(ObsAvoidance._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qi", self.timestampMs, self.count))
        buf.write(struct.pack('>%dd' % self.count, *self.angles[:self.count]))
        buf.write(struct.pack('>%dd' % self.count, *self.ranges[:self.count]))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != ObsAvoidance._get_packed_fingerprint():
            raise ValueError("Decode error")
        return ObsAvoidance._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = ObsAvoidance()
        self.timestampMs, self.count = struct.unpack(">qi", buf.read(12))
        self.angles = struct.unpack('>%dd' % self.count, buf.read(self.count * 8))
        self.ranges = struct.unpack('>%dd' % self.count, buf.read(self.count * 8))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if ObsAvoidance in parents: return 0
        tmphash = (0xdfccc85b3d2409d8) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if ObsAvoidance._packed_fingerprint is None:
            ObsAvoidance._packed_fingerprint = struct.pack(">Q", ObsAvoidance._get_hash_recursive([]))
        return ObsAvoidance._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", ObsAvoidance._get_packed_fingerprint())[0]

