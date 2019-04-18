//
//  VMELog+CoreDataProperties.m
//  
//
//  Created by Jenkins on 21/12/2018.
//
//  This file was automatically generated and should not be edited.
//

#import "VMELog+CoreDataProperties.h"

@implementation VMELog (CoreDataProperties)

+ (NSFetchRequest<VMELog *> *)fetchRequest {
	return [NSFetchRequest fetchRequestWithEntityName:@"VMELog"];
}

@dynamic data;

@end
