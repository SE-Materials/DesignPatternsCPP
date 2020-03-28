//
//  Event.h
//  DesignPatterns
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#ifndef Event_h
#define Event_h

struct Event {
    virtual void Print() = 0;
    virtual ~Event() = default;
};

#endif /* Event_h */
