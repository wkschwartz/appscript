//
//  specifier.h
//  AppscriptTEST
//
//  Created by Hamish Sanderson on 24/01/2007.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include <Carbon/Carbon.h>

/**********************************************************************/


#define AEMApp [AEMApplicationRoot reference]
#define AEMCon [AEMCurrentContainerRoot reference]
#define AEMIts [AEMObjectBeingExaminedRoot]


/**********************************************************************/
// constants

// insertion locations
static NSAppleEventDescriptor *kEnumBeginning,
							  *kEnumEnd,
							  *kEnumBefore,
							  *kEnumAfter;

// relative positions
static NSAppleEventDescriptor *kEnumPrevious,
							  *kEnumNext;

// absolute ordinals
static NSAppleEventDescriptor *kOrdinalFirst,
							  *kOrdinalMiddle,
							  *kOrdinalLast,
							  *kOrdinalAny,
							  *kOrdinalAll;

// key forms
static NSAppleEventDescriptor *kFormPropertyID,
							  *kFormUserPropertyID,
							  *kFormName,
							  *kFormAbsolutePosition,
							  *kFormUniqueID,
							  *kFormRelativePosition,
							  *kFormRange,
							  *kFormTest;


// prepacked value for keyDesiredClass for use by -packSelf: in property specifiers
static NSAppleEventDescriptor *kClassProperty;

// blank record used by -packSelf: to construct object specifiers
static NSAppleEventDescriptor *kNullRecord;


void initSpecifierModule(void);

void disposeSpecifierModule(void);


/**********************************************************************/


@interface AEMResolver // TO DO

- (id)app;

@end


@interface AEMCodecs : NSObject

- (NSAppleEventDescriptor *)pack:(id)object;

- (id)unpack:(NSAppleEventDescriptor *)desc;

@end


/**********************************************************************/
// AEM reference base (shared by specifiers and tests)

@interface AEMBase : NSObject

/*
 * TO DO:
 *	- (unsigned)hash;
 *	- (BOOL)isEqual:(id)object;
 *	- (NSArray *)comparableData;
 */
 
@end


/**********************************************************************/
// Specifier base

/*
 * Abstract base class for all object specifier classes.
 */
@interface AEMSpecifier : AEMBase {
	AEMSpecifier *container;
	NSAppleEventDescriptor *keyForm;
	id key;
	NSAppleEventDescriptor *cachedDesc;
}

- (id)initWithContainer:(AEMSpecifier *)container_ key:(id)key_;

// reserved methods

- (id)root;
- (id)trueSelf;
- (id)packSelf:(id)codecs;

-(id)resolve:(id)object;

@end


/**********************************************************************/
// Insertion location specifier

/*
 * A reference to an element insertion point.
 */
@interface AEMInsertionSpecifier : AEMSpecifier
@end


/**********************************************************************/
// Position specifier base

/*
 * All property and element reference forms inherit from this abstract class.
 */
@interface AEMPositionSpecifierBase : AEMSpecifier {
	OSType wantCode;
}

- (id)initWithContainer:(AEMSpecifier *)container_ key:(id)key_ wantCode:(OSType)wantCode_;

// TO DO: methods for constructing comparison and logic tests

// Insertion location selectors

- (AEMInsertionSpecifier *)start;
- (AEMInsertionSpecifier *)end;
- (AEMInsertionSpecifier *)before;
- (AEMInsertionSpecifier *)after;

// property and all-element specifiers

// TO DO: specific return types
- (id)property:(OSType)propertyCode;
- (id)userProperty:(NSString *)propertyName;
- (id)elements:(OSType)classCode;

// by-relative-position selectors // TO DO

// - (AEMElementByRelativePositionSpecifier *)previous:(OSType)classCode;
// - (AEMElementByRelativePositionSpecifier *)next:(OSType)classCode;

@end


/**********************************************************************/
// Properties

/*
 * Specifier identifying an application-defined property
 */
@interface AEMPropertySpecifier : AEMPositionSpecifierBase
@end


@interface AEMUserPropertySpecifier : AEMPositionSpecifierBase
@end


/**********************************************************************/
// Single elements

/*
 * Abstract base class for all single element specifiers
 */
@interface AEMSingleElementSpecifierBase : AEMPositionSpecifierBase
@end

/*
 * Specifiers identifying a single element by name, index, id or named ordinal
 */
@interface AEMElementByNameSpecifier : AEMSingleElementSpecifierBase
@end

@interface AEMElementByIndexSpecifier : AEMSingleElementSpecifierBase
@end

@interface AEMElementByIDSpecifier : AEMSingleElementSpecifierBase
@end

@interface AEMElementByOrdinalSpecifier : AEMSingleElementSpecifierBase
@end

// TO DO: AEMElementByRelativePositionSpecifier


/**********************************************************************/
// Multiple elements

/*
 * Base class for all multiple element specifiers.
 */
@interface AEMMultipleElementsSpecifierBase : AEMPositionSpecifierBase 

// ordinal selectors

- (AEMElementByOrdinalSpecifier *)first;
- (AEMElementByOrdinalSpecifier *)middle;
- (AEMElementByOrdinalSpecifier *)last;
- (AEMElementByOrdinalSpecifier *)any;

// by-index, by-name, by-id selectors
 
- (AEMElementByIndexSpecifier *)at:(long)index;
- (AEMElementByIndexSpecifier *)byIndex:(id)index; // normally NSNumber, but may occasionally be other types
- (AEMElementByNameSpecifier *)byName:(NSString *)name;
- (AEMElementByIDSpecifier *)byID:(id)id_;

// by-range selector

// TO DO: specific return type
- (id)at:(long)fromIndex to:(long)toIndex;
- (id)byRange:(id)fromObject to:(id)toObject; // takes two con-based references, with other values being expanded as necessary

// by-test selector

- (id)byTest:(id)testReference; // TO DO: specific param, return types

@end


@interface AEMElementsByRangeSpecifier : AEMMultipleElementsSpecifierBase
@end


@interface AEMElementsByTestSpecifier : AEMMultipleElementsSpecifierBase
@end


@interface AEMAllElementsSpecifier : AEMMultipleElementsSpecifierBase
@end


/**********************************************************************/
// Multiple element shim

@interface AEMUnkeyedElementsShim : AEMSpecifier {
	OSType wantCode;
}

- (id)initWithContainer:(AEMSpecifier *)container_ wantCode:(OSType)wantCode_;

@end


/**********************************************************************/
// Reference roots

@interface AEMReferenceRootBase : AEMPositionSpecifierBase

+ (id)reference;

@end

@interface AEMApplicationRoot : AEMReferenceRootBase
@end

@interface AEMCurrentContainerRoot : AEMReferenceRootBase
@end

@interface AEMObjectBeingExaminedRoot : AEMReferenceRootBase
@end

