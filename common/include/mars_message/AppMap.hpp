/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __mars_message_AppMap_hpp__
#define __mars_message_AppMap_hpp__

#include <lcm/lcm_coretypes.h>

#include <vector>
#include <string>
#include "mars_message/Pose.hpp"
#include "mars_message/Pose.hpp"
#include "mars_message/AppRoomProperties.hpp"
#include "mars_message/Polygon.hpp"

namespace mars_message
{

class AppMap
{
    public:
        int8_t     version;

        int16_t    mapId;

        int8_t     type;

        int16_t    width;

        int16_t    height;

        mars_message::Pose origin;

        float      resolution;

        mars_message::Pose charger;

        int32_t    pointCount;

        std::vector< int8_t > data;

        int16_t    roomNum;

        std::vector< mars_message::AppRoomProperties > roomPropeties;

        std::vector< std::string > roomName;

        std::vector< mars_message::Polygon > roomPolygon;

    public:
        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline int encode(void *buf, int offset, int maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline int getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to read while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline int decode(const void *buf, int offset, int maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "AppMap"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static uint64_t _computeHash(const __lcm_hash_ptr *p);
};

int AppMap::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int AppMap::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int AppMap::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t AppMap::getHash()
{
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* AppMap::getTypeName()
{
    return "AppMap";
}

int AppMap::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, &this->version, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int16_t_encode_array(buf, offset + pos, maxlen - pos, &this->mapId, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, &this->type, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int16_t_encode_array(buf, offset + pos, maxlen - pos, &this->width, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int16_t_encode_array(buf, offset + pos, maxlen - pos, &this->height, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->origin._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->resolution, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->charger._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->pointCount, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->pointCount > 0) {
        tlen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, &this->data[0], this->pointCount);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __int16_t_encode_array(buf, offset + pos, maxlen - pos, &this->roomNum, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    for (int a0 = 0; a0 < this->roomNum; a0++) {
        tlen = this->roomPropeties[a0]._encodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    for (int a0 = 0; a0 < this->roomNum; a0++) {
        char* __cstr = const_cast<char*>(this->roomName[a0].c_str());
        tlen = __string_encode_array(
            buf, offset + pos, maxlen - pos, &__cstr, 1);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    for (int a0 = 0; a0 < this->roomNum; a0++) {
        tlen = this->roomPolygon[a0]._encodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    return pos;
}

int AppMap::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, &this->version, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int16_t_decode_array(buf, offset + pos, maxlen - pos, &this->mapId, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, &this->type, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int16_t_decode_array(buf, offset + pos, maxlen - pos, &this->width, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int16_t_decode_array(buf, offset + pos, maxlen - pos, &this->height, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->origin._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->resolution, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->charger._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->pointCount, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->pointCount) {
        this->data.resize(this->pointCount);
        tlen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, &this->data[0], this->pointCount);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __int16_t_decode_array(buf, offset + pos, maxlen - pos, &this->roomNum, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    try {
        this->roomPropeties.resize(this->roomNum);
    } catch (...) {
        return -1;
    }
    for (int a0 = 0; a0 < this->roomNum; a0++) {
        tlen = this->roomPropeties[a0]._decodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    try {
        this->roomName.resize(this->roomNum);
    } catch (...) {
        return -1;
    }
    for (int a0 = 0; a0 < this->roomNum; a0++) {
        int32_t __elem_len;
        tlen = __int32_t_decode_array(
            buf, offset + pos, maxlen - pos, &__elem_len, 1);
        if(tlen < 0) return tlen; else pos += tlen;
        if(__elem_len > maxlen - pos) return -1;
        this->roomName[a0].assign(static_cast<const char*>(buf) + offset + pos, __elem_len -  1);
        pos += __elem_len;
    }

    try {
        this->roomPolygon.resize(this->roomNum);
    } catch (...) {
        return -1;
    }
    for (int a0 = 0; a0 < this->roomNum; a0++) {
        tlen = this->roomPolygon[a0]._decodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    return pos;
}

int AppMap::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += __int8_t_encoded_array_size(NULL, 1);
    enc_size += __int16_t_encoded_array_size(NULL, 1);
    enc_size += __int8_t_encoded_array_size(NULL, 1);
    enc_size += __int16_t_encoded_array_size(NULL, 1);
    enc_size += __int16_t_encoded_array_size(NULL, 1);
    enc_size += this->origin._getEncodedSizeNoHash();
    enc_size += __float_encoded_array_size(NULL, 1);
    enc_size += this->charger._getEncodedSizeNoHash();
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int8_t_encoded_array_size(NULL, this->pointCount);
    enc_size += __int16_t_encoded_array_size(NULL, 1);
    for (int a0 = 0; a0 < this->roomNum; a0++) {
        enc_size += this->roomPropeties[a0]._getEncodedSizeNoHash();
    }
    for (int a0 = 0; a0 < this->roomNum; a0++) {
        enc_size += this->roomName[a0].size() + 4 + 1;
    }
    for (int a0 = 0; a0 < this->roomNum; a0++) {
        enc_size += this->roomPolygon[a0]._getEncodedSizeNoHash();
    }
    return enc_size;
}

uint64_t AppMap::_computeHash(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for(fp = p; fp != NULL; fp = fp->parent)
        if(fp->v == AppMap::getHash)
            return 0;
    const __lcm_hash_ptr cp = { p, AppMap::getHash };

    uint64_t hash = 0xdb662f04d8462b98LL +
         mars_message::Pose::_computeHash(&cp) +
         mars_message::Pose::_computeHash(&cp) +
         mars_message::AppRoomProperties::_computeHash(&cp) +
         mars_message::Polygon::_computeHash(&cp);

    return (hash<<1) + ((hash>>63)&1);
}

}

#endif
