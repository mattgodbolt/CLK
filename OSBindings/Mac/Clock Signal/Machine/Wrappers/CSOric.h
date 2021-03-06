//
//  CSOric.h
//  Clock Signal
//
//  Created by Thomas Harte on 11/10/2016.
//  Copyright © 2016 Thomas Harte. All rights reserved.
//

#import "CSMachine.h"
#import "CSFastLoading.h"

@interface CSOric : CSMachine <CSFastLoading>

- (instancetype)init;

@property (nonatomic, assign) BOOL useFastLoadingHack;
@property (nonatomic, assign) BOOL useCompositeOutput;

@end
