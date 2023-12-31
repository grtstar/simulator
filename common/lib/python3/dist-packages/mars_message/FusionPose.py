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

class FusionPose(object):
    __slots__ = ["timetickMs", "pose", "rawYaw"]

    __typenames__ = ["int64_t", "mars_message.Pose", "float"]

    __dimensions__ = [None, None, None]

    def __init__(self):
        self.timetickMs = 0
        self.pose = mars_message.Pose()
        self.rawYaw = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(FusionPose._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">q", self.timetickMs))
        assert self.pose._get_packed_fingerprint() == mars_message.Pose._get_packed_fingerprint()
        self.pose._encode_one(buf)
        buf.write(struct.pack(">f", self.rawYaw))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != FusionPose._get_packed_fingerprint():
            raise ValueError("Decode error")
        return FusionPose._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = FusionPose()
        self.timetickMs = struct.unpack(">q", buf.read(8))[0]
        self.pose = mars_message.Pose._decode_one(buf)
        self.rawYaw = struct.unpack(">f", buf.read(4))[0]
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if FusionPose in parents: return 0
        newparents = parents + [FusionPose]
        tmphash = (0x112f8b8ea2e2d07b+ mars_message.Pose._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if FusionPose._packed_fingerprint is None:
            FusionPose._packed_fingerprint = struct.pack(">Q", FusionPose._get_hash_recursive([]))
        return FusionPose._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", FusionPose._get_packed_fingerprint())[0]

