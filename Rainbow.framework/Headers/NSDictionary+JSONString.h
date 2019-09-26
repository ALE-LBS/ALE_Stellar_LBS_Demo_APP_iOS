/*
 * Rainbow
 *
 * Copyright (c) 2016, ALE International
 * All rights reserved.
 *
 * ALE International Proprietary Information
 *
 * Contains proprietary/trade secret information which is the property of
 * ALE International and must not be made available to, or copied or used by
 * anyone outside ALE International without its written authorization
 *
 * Not to be disclosed or used except in accordance with applicable agreements.
 */

#import <Foundation/Foundation.h>

@interface NSDictionary (JSONString)
/**
 *  return a json string from a NSDictionary
 *
 *  @param prettyPrint Specifies that the JSON data should be generated with whitespace designed to make the output more readable. If this option is not set, the most compact possible JSON representation is generated.
 *
 *  @return json string representation, empty dictionary in case of error in json parsing
 */
-(NSString*) jsonStringWithPrettyPrint:(BOOL) prettyPrint;
@end
