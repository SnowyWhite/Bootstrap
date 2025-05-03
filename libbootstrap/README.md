# libbootstrap - A C++ library

The `libbootstrap` C++ library provides <SUMMARY-OF-FUNCTIONALITY>.


## Usage

To start using `libbootstrap` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libbootstrap ^<VERSION>
```

Then import the library in your `buildfile`:

```
import libs = libbootstrap%lib{<TARGET>}
```


## Importable targets

This package provides the following importable targets:

```
lib{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.libbootstrap.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>
