#pragma once
class EventListener {
public:
    virtual void onEventOccurred(int row, int column) = 0; 
};