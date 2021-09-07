#pragma once

struct Action
{
    enum
    {
        move,
        turn,
        write,
        setState
    };
    int type, argument;
};
