// Copyright 2022 KURZ Digital Solutions GmbH
//
// SPDX-License-Identifier: Apache-2.0

#import <CoreGraphics/CoreGraphics.h>
#import <CoreImage/CoreImage.h>
#import "ZXIResult.h"
#import "ZXIDecodeHints.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZXIBarcodeReader : NSObject
@property(nonatomic, strong) ZXIDecodeHints *hints;

- (instancetype)initWithHints:(ZXIDecodeHints*)options;
- (nullable NSArray<ZXIResult *> *)readCIImage:(nonnull CIImage *)image error:(NSError **)error;
- (nullable NSArray<ZXIResult *> *)readCGImage:(nonnull CGImageRef)image error:(NSError **)error;
@end

NS_ASSUME_NONNULL_END
