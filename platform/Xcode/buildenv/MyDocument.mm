//
//  MyDocument.m
//  midi-me
//
//  Created by Jeroen Dierckx on 22/07/09.
//  Copyright EDM 2009 . All rights reserved.
//

#import "MyDocument.h"

#include <libMidi-Me/Chain.h>

@interface MyDocument (Private)
-(void) step:(NSTimer *)theTimer;
@end

@implementation MyDocument

- (id)init
{
	if(!(self = [super init]))
		return nil;

	// Initialize
	m_pChain = new MidiMe::Chain();
	
	// Start chain
	m_timer = [NSTimer scheduledTimerWithTimeInterval:0.01 target:self selector:@selector(step:) userInfo:nil repeats:YES];

    return self;
}

-(void) dealloc
{
	delete m_pChain;

	[super dealloc];
}

- (NSString *)windowNibName
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"MyDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
    // Add any code here that needs to be executed once the windowController has loaded the document's window.
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to write your document to data of the specified type. If the given outError != NULL, ensure that you set *outError when returning nil.

    // You can also choose to override -fileWrapperOfType:error:, -writeToURL:ofType:error:, or -writeToURL:ofType:forSaveOperation:originalContentsURL:error: instead.

    // For applications targeted for Panther or earlier systems, you should use the deprecated API -dataRepresentationOfType:. In this case you can also choose to override -fileWrapperRepresentationOfType: or -writeToFile:ofType: instead.

    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
	return nil;
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to read your document from the given data of the specified type.  If the given outError != NULL, ensure that you set *outError when returning NO.

    // You can also choose to override -readFromFileWrapper:ofType:error: or -readFromURL:ofType:error: instead. 
    
    // For applications targeted for Panther or earlier systems, you should use the deprecated API -loadDataRepresentation:ofType. In this case you can also choose to override -readFromFile:ofType: or -loadFileWrapperRepresentation:ofType: instead.
    
    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
    return YES;
}


-(void) step:(NSTimer *)theTimer
{
	// Step the Midi-Me chain
	float seconds = (float) m_timer.timeInterval;
	m_pChain->step(seconds);
}

@end
