/*
 * This file is part of the Aaru Data Preservation Suite.
 * Copyright (c) 2019-2022 Natalia Portillo.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBAARUFORMAT_CONTEXT_H
#define LIBAARUFORMAT_CONTEXT_H

#include "lru.h"
#include "structs.h"

#ifndef MD5_DIGEST_LENGTH
#define MD5_DIGEST_LENGTH 16
#endif

#ifndef SHA1_DIGEST_LENGTH
#define SHA1_DIGEST_LENGTH 20
#endif

#ifndef SHA256_DIGEST_LENGTH
#define SHA256_DIGEST_LENGTH 32
#endif

typedef struct Checksums
{
    bool     hasMd5;
    bool     hasSha1;
    bool     hasSha256;
    bool     hasSpamSum;
    uint8_t  md5[MD5_DIGEST_LENGTH];
    uint8_t  sha1[SHA1_DIGEST_LENGTH];
    uint8_t  sha256[SHA256_DIGEST_LENGTH];
    uint8_t *spamsum;
} Checksums;

typedef struct mediaTagEntry
{
    uint8_t       *data;
    int32_t        type;
    uint32_t       length;
    UT_hash_handle hh;
} mediaTagEntry;

typedef struct aaruformatContext
{
    uint64_t                            magic;
    uint8_t                             libraryMajorVersion;
    uint8_t                             libraryMinorVersion;
    FILE                               *imageStream;
    AaruHeader                          header;
    uint8_t                            *sectorPrefix;
    uint8_t                            *sectorPrefixCorrected;
    uint8_t                            *sectorSuffix;
    uint8_t                            *sectorSuffixCorrected;
    uint8_t                            *sectorSubchannel;
    uint8_t                            *mode2Subheaders;
    uint8_t                             shift;
    bool                                inMemoryDdt;
    uint64_t                           *userDataDdt;
    size_t                              mappedMemoryDdtSize;
    uint32_t                           *sectorPrefixDdt;
    uint32_t                           *sectorSuffixDdt;
    GeometryBlockHeader                 geometryBlock;
    MetadataBlockHeader                 metadataBlockHeader;
    uint8_t                            *metadataBlock;
    TracksHeader                        tracksHeader;
    TrackEntry                         *trackEntries;
    CicmMetadataBlock                   cicmBlockHeader;
    uint8_t                            *cicmBlock;
    DumpHardwareHeader                  dumpHardwareHeader;
    struct DumpHardwareEntriesWithData *dumpHardwareEntriesWithData;
    struct ImageInfo                    imageInfo;
    CdEccContext                       *eccCdContext;
    uint8_t                             numberOfDataTracks;
    TrackEntry                         *dataTracks;
    bool                               *readableSectorTags;
    struct CacheHeader                  blockHeaderCache;
    struct CacheHeader                  blockCache;
    struct Checksums                    checksums;
    struct mediaTagEntry               *mediaTags;
} aaruformatContext;

typedef struct DumpHardwareEntriesWithData
{
    DumpHardwareEntry  entry;
    struct DumpExtent *extents;
    uint8_t           *manufacturer;
    uint8_t           *model;
    uint8_t           *revision;
    uint8_t           *firmware;
    uint8_t           *serial;
    uint8_t           *softwareName;
    uint8_t           *softwareVersion;
    uint8_t           *softwareOperatingSystem;
} DumpHardwareEntriesWithData;

#pragma pack(push, 1)

typedef struct DumpExtent
{
    uint64_t start;
    uint64_t end;
} DumpExtent;

#pragma pack(pop)

#endif  // LIBAARUFORMAT_CONTEXT_H
