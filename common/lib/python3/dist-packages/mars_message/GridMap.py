"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import mars_message.Pose

class GridMap(object):
    __slots__ = ["timestampMs", "mapLoadTime", "resolution", "width", "height", "origin", "pointCount", "data"]

    __typenames__ = ["int64_t", "int64_t", "float", "int32_t", "int32_t", "mars_message.Pose", "int32_t", "int8_t"]

    __dimensions__ = [None, None, None, None, None, None, None, ["pointCount"]]

    def __init__(self):
        self.timestampMs = 0
        self.mapLoadTime = 0
        self.resolution = 0.0
        self.width = 0
        self.height = 0
        self.origin = mars_message.Pose()
        self.pointCount = 0
        self.data = []

    def encode(self):
        buf = BytesIO()
        buf.write(GridMap._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qqfii", self.timestampMs, self.mapLoadTime, self.resolution, self.width, self.height))
        assert self.origin._get_packed_fingerprint() == mars_message.Pose._get_packed_fingerprint()
        self.origin._encode_one(buf)
        buf.write(struct.pack(">i", self.pointCount))
        buf.write(struct.pack('>%db' % self.pointCount, *self.data[:self.pointCount]))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != GridMap._get_packed_fingerprint():
            raise ValueError("Decode error")
        return GridMap._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = GridMap()
        self.timestampMs, self.mapLoadTime, self.resolution, self.width, self.height = struct.unpack(">qqfii", buf.read(28))
        self.origin = mars_message.Pose._decode_one(buf)
        self.pointCount = struct.unpack(">i", buf.read(4))[0]
        self.data = struct.unpack('>%db' % self.pointCount, buf.read(self.pointCount))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if GridMap in parents: return 0
        newparents = parents + [GridMap]
        tmphash = (0xb1198c74f267aebb+ mars_message.Pose._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if GridMap._packed_fingerprint is None:
            GridMap._packed_fingerprint = struct.pack(">Q", GridMap._get_hash_recursive([]))
        return GridMap._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", GridMap._get_packed_fingerprint())[0]

