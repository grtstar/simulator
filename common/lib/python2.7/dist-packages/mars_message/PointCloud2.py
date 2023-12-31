"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import mars_message.Point

class PointCloud2(object):
    __slots__ = ["timestampMs", "scanTime", "count", "points", "intensities"]

    __typenames__ = ["int64_t", "float", "int32_t", "mars_message.Point", "float"]

    __dimensions__ = [None, None, None, ["count"], ["count"]]

    def __init__(self):
        self.timestampMs = 0
        self.scanTime = 0.0
        self.count = 0
        self.points = []
        self.intensities = []

    def encode(self):
        buf = BytesIO()
        buf.write(PointCloud2._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qfi", self.timestampMs, self.scanTime, self.count))
        for i0 in range(self.count):
            assert self.points[i0]._get_packed_fingerprint() == mars_message.Point._get_packed_fingerprint()
            self.points[i0]._encode_one(buf)
        buf.write(struct.pack('>%df' % self.count, *self.intensities[:self.count]))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != PointCloud2._get_packed_fingerprint():
            raise ValueError("Decode error")
        return PointCloud2._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = PointCloud2()
        self.timestampMs, self.scanTime, self.count = struct.unpack(">qfi", buf.read(16))
        self.points = []
        for i0 in range(self.count):
            self.points.append(mars_message.Point._decode_one(buf))
        self.intensities = struct.unpack('>%df' % self.count, buf.read(self.count * 4))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if PointCloud2 in parents: return 0
        newparents = parents + [PointCloud2]
        tmphash = (0xa70744f80b87fabd+ mars_message.Point._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if PointCloud2._packed_fingerprint is None:
            PointCloud2._packed_fingerprint = struct.pack(">Q", PointCloud2._get_hash_recursive([]))
        return PointCloud2._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", PointCloud2._get_packed_fingerprint())[0]

