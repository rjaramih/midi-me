//
//  MyDocument.h
//  midi-me
//
//  Created by Jeroen Dierckx on 22/07/09.
//  Copyright EDM 2009 . All rights reserved.
//


#import <Cocoa/Cocoa.h>
namespace MidiMe { class Chain; }

@interface MyDocument : NSDocument
{
	// Midi-Me chain
	MidiMe::Chain *m_pChain;
	
	// Timer
	NSTimer *m_timer;
}
@end
