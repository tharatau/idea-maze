# Tau Lang

# Specification

## Design

- No uninitialised variables
- Single pass compiler

## Language

### Variable

```
var v: int8 = 7;
```

### Pointer

```
ptr v: int8 = &a;
```

### Function

```
fun f(x: int8): int8 {
    return x;
};
```

### For

```
var v: int8 = 1;
for(var i: int8 = 0; i < 9; i = i + 1) {
    v = v + i;
}
```

## Iff

```
var a: int8 = 7;
var b: int8 = 2;

iff (a > b) {
    return a - b;
} else iff (a == b) {
    return 0;
} else {
    return b - a;
}
```

## Structure

```
str s {
    var v1: int8;
    var v2: int8;
    fun f1(): int8 {
        return s.v1 + s.v2;
    }
};
```

## Module resolution

Define a module:
```
mod m;

fun f(x: int8): int8 {
    return x;
}

y = f(3);
```

Require a module:
```
req m;

fun main():int8 {
    m.f(5);
    return 0;
}
```
