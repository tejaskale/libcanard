/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016-2017 UAVCAN Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Contributors: https://github.com/UAVCAN/libcanard/contributors
 */

/*
 * This file holds function declarations that expose the library's internal definitions for unit testing.
 * It is NOT part of the library's API and should not even be looked at by the user.
 */

#ifndef DRONECANARD_INTERNALS_H
#define DRONECANARD_INTERNALS_H

#include "canard.h"

#ifdef __cplusplus
extern "C" {
#endif

/// This macro is needed only for testing and development. Do not redefine this in production.
#ifndef DRONECANARD_INTERNAL
# define DRONECANARD_INTERNAL static
#endif


DRONECANARD_INTERNAL DroneCanardRxState* traverseRxStates(DroneCanardInstance* ins,
                                                uint32_t transfer_descriptor);

DRONECANARD_INTERNAL DroneCanardRxState* createRxState(DroneCanardPoolAllocator* allocator,
                                             uint32_t transfer_descriptor);

DRONECANARD_INTERNAL DroneCanardRxState* prependRxState(DroneCanardInstance* ins,
                                              uint32_t transfer_descriptor);

DRONECANARD_INTERNAL DroneCanardRxState* findRxState(DroneCanardRxState* state,
                                           uint32_t transfer_descriptor);

DRONECANARD_INTERNAL int16_t bufferBlockPushBytes(DroneCanardPoolAllocator* allocator,
                                             DroneCanardRxState* state,
                                             const uint8_t* data,
                                             uint8_t data_len);

DRONECANARD_INTERNAL DroneCanardBufferBlock* createBufferBlock(DroneCanardPoolAllocator* allocator);

DRONECANARD_INTERNAL DroneCanardTransferType extractTransferType(uint32_t id);

DRONECANARD_INTERNAL uint16_t extractDataType(uint32_t id);

DRONECANARD_INTERNAL void pushTxQueue(DroneCanardInstance* ins,
                                 DroneCanardTxQueueItem* item);

DRONECANARD_INTERNAL bool isPriorityHigher(uint32_t id,
                                      uint32_t rhs);

DRONECANARD_INTERNAL DroneCanardTxQueueItem* createTxItem(DroneCanardPoolAllocator* allocator);

DRONECANARD_INTERNAL void prepareForNextTransfer(DroneCanardRxState* state);

DRONECANARD_INTERNAL int16_t computeTransferIDForwardDistance(uint8_t a,
                                                         uint8_t b);

DRONECANARD_INTERNAL void incrementTransferID(uint8_t* transfer_id);

DRONECANARD_INTERNAL uint64_t releaseStatePayload(DroneCanardInstance* ins,
                                             DroneCanardRxState* rxstate);

DRONECANARD_INTERNAL uint8_t dlcToDataLength(uint8_t dlc);
DRONECANARD_INTERNAL uint8_t dataLengthToDlc(uint8_t data_length);

/// Returns the number of frames enqueued
DRONECANARD_INTERNAL int16_t enqueueTxFrames(DroneCanardInstance* ins,
                                        uint32_t can_id,
                                        uint8_t* transfer_id,
                                        const uint8_t* payload,
                                        uint16_t payload_len
#if DRONECANARD_MULTI_IFACE
                                        ,uint8_t iface_mask
#endif
#if DRONECANARD_ENABLE_CANFD
                                        ,bool canfd
#endif
                                        );

DRONECANARD_INTERNAL void copyBitArray(const uint8_t* src,
                                  uint32_t src_offset,
                                  uint32_t src_len,
                                  uint8_t* dst,
                                  uint32_t dst_offset);

/**
 * Moves specified bits from the scattered transfer storage to a specified contiguous buffer.
 * Returns the number of bits copied, or negated error code.
 */
DRONECANARD_INTERNAL int16_t descatterTransferPayload(const DroneCanardRxTransfer* transfer,
                                                 uint32_t bit_offset,
                                                 uint8_t bit_length,
                                                 void* output);

DRONECANARD_INTERNAL bool isBigEndian(void);

DRONECANARD_INTERNAL void swapByteOrder(void* data, unsigned size);

/*
 * Transfer CRC
 */
DRONECANARD_INTERNAL uint16_t crcAddByte(uint16_t crc_val,
                                    uint8_t byte);

DRONECANARD_INTERNAL uint16_t crcAddSignature(uint16_t crc_val,
                                         uint64_t data_type_signature);

DRONECANARD_INTERNAL uint16_t crcAdd(uint16_t crc_val,
                                const uint8_t* bytes,
                                size_t len);

/**
 * Inits a memory allocator.
 *
 * @param [in] allocator The memory allocator to initialize.
 * @param [in] buf The buffer used by the memory allocator.
 * @param [in] buf_len The number of blocks in buf.
 */
DRONECANARD_INTERNAL void initPoolAllocator(DroneCanardPoolAllocator* allocator,
                                       DroneCanardPoolAllocatorBlock* buf,
                                       uint16_t buf_len);

/**
 * Allocates a block from the given pool allocator.
 */
DRONECANARD_INTERNAL void* allocateBlock(DroneCanardPoolAllocator* allocator);

/**
 * Frees a memory block previously returned by canardAllocateBlock.
 */
DRONECANARD_INTERNAL void freeBlock(DroneCanardPoolAllocator* allocator,
                               void* p);

#ifdef __cplusplus
}
#endif
#endif
