package main

import (
    "fmt"
    "sync"
)

type Key string
type Value int
type Dictionary struct {
    items map[Key]Value
    lock  sync.RWMutex
}

func (d *Dictionary) Set(k Key, v Value) {
    d.lock.Lock()
    defer d.lock.Unlock()
    if d.items == nil {
        d.items = make(map[Key]Value)
    }
    d.items[k] = v
    fmt.Printf("Set key: %s, val: %d\n", k, d.items[k]);
}

func (d *Dictionary) Delete(k Key) bool {
    d.lock.Lock()
    defer d.lock.Unlock()
    _, ok := d.items[k]
    if ok {
        delete(d.items, k)
    }
    return ok
}

func (d *Dictionary) Has(k Key) bool {
    d.lock.RLock()
    defer d.lock.RUnlock()
    _, ok := d.items[k]
    return ok
}

func (d *Dictionary) Get(k Key) Value {
    d.lock.RLock()
    defer d.lock.RUnlock()
    return d.items[k]
}

func (d *Dictionary) Clear() {
    d.lock.Lock()
    defer d.lock.Unlock()
    d.items = make(map[Key]Value)
}

func (d *Dictionary) Size() int {
    d.lock.RLock()
    defer d.lock.RUnlock()
    return len(d.items)
}

func (d *Dictionary) Keys() []Key {
    d.lock.RLock()
    defer d.lock.RUnlock()
    keys := []Key{}
    for i := range d.items {
        keys = append(keys, i)
    }
    return keys
}

func (d *Dictionary) Values() []Value {
    d.lock.RLock()
    defer d.lock.RUnlock()
    values := []Value{}
    for i := range d.items {
        values = append(values, d.items[i])
    }
    return values
}

func main() {
    dict := Dictionary{}
    dict.Set("dude", 42)
    dict.Set("wudup", 17)
    sz := dict.Size()
    fmt.Println("sz: ", sz)
    keys := dict.Keys()
    for _,k := range keys {
        fmt.Println("k: ", k)
    }
    for _,v := range dict.Values() {
        fmt.Println("v: ", v)
    }
    var str Key = "dude"
    fmt.Println("Get: ", dict.Get(str))
    if dict.Has(str) {
        fmt.Println("Has: ", str)
    } else {
        fmt.Println("Has not: ", str)
    }
    dict.Delete("dude")
    dict.Clear()
}

