#!/usr/bin/env python3.8

import asyncio
import time

async def say_after(delay, what):
    await asyncio.sleep(delay)
    try:
        print(what)
    finally:
        print('dude')

async def main():
    print(f"started at {time.strftime('%X')}")
    await say_after(1, 'hello')
    await say_after(2, 'hello')
    print(f"finished at {time.strftime('%X')}")

if __name__ == '__main__':
    print("sup")
    asyncio.run(main())

