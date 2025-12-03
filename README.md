# Refactoring to use [lexbor_erl](https://github.com/f34nk/lexbor_erl/tree/master) in progress - please stay tuned!


[![CI](https://github.com/f34nk/modest_ex/actions/workflows/ci.yml/badge.svg)](https://github.com/f34nk/modest_ex/actions)
[![ModestEx version](https://img.shields.io/hexpm/v/modest_ex.svg)](https://hex.pm/packages/modest_ex)
[![Hex.pm](https://img.shields.io/hexpm/dt/modest_ex.svg)](https://hex.pm/packages/modest_ex)

![humble by Eliricon from the Noun Project](https://github.com/f34nk/modest_ex/blob/master/modest_ex_icon.png)

# ModestEx

A library to do pipeable transformations on html strings with CSS selectors, e.g. find(), prepend(), append(), replace() etc.

Elixir wrapper for lexborisov's ~~**Modest**~~ **Lexbor** C Library.

>Lexbor browser engine crafted entirely in C (there's no school like the old school)

- [~~Modest~~](https://github.com/lexborisov/Modest)
  [Lexbor](https://github.com/lexborisov/Lexbor)
  - HTML5 parsing library in pure C99
  - fully conformant with the HTML5 spec

All Lexbor-related features are implemented as a port binding through the Erlang [lexbor_erl](https://github.com/f34nk/lexbor_erl) library.

For news and updates please check out the [forum discussion](https://elixirforum.com/t/modestex-pipeable-transformations-on-html-strings-with-css-selectors/12793/18).

## Example

Total **16** features implemented. See [**complete feature list**](https://github.com/f34nk/modest_ex/blob/master/FEATURES.md).

Build transformation pipelines...

```elixir
test "build up a complete DOM" do
  result = ""
  |> ModestEx.serialize()
  |> ModestEx.append("body", "<div>")
  |> ModestEx.set_attribute("div", "class", "col-md-12")
  |> ModestEx.append("div", "<div>")
  |> ModestEx.set_attribute("div.col-md-12 div", "class", "col-md-6")
  |> ModestEx.append("div.col-md-12 div", "<a></a>")
  |> ModestEx.set_text("a", "Hello")

  copy = ModestEx.find(result, "div.col-md-12 div")
  |> ModestEx.set_text("a", "World")
  
  result = ModestEx.insert_after(result, "div.col-md-12 div", copy)
  |> ModestEx.set_attribute("div.col-md-6:first-of-type a", "href", "https://elixir-lang.org")
  |> ModestEx.set_attribute("div.col-md-6:last-of-type a", "href", "https://google.de")
  
  assert result == "<div class=\"col-md-12\"><div class=\"col-md-6\"><a href=\"https://elixir-lang.org\">Hello</a></div><div class=\"col-md-6\"><a href=\"https://google.de\">World</a></div></div>"
end
```

## Breaking Changes 

Please note, after migrating to [lexbor_erl](https://github.com/f34nk/lexbor_erl/tree/master) not all features are supported.
See [CHANGELOG](https://github.com/f34nk/modest_ex/blob/master/CHANGELOG.md)

## Supported CSS Selectors

All common CSS Selectors are supported. Total **38** selector patterns implemented.
See [**complete list of supported CSS selectors**](https://github.com/f34nk/modest_ex/blob/master/SELECTORS.md).


## Installation

Available on [hex](https://hex.pm/packages/modest_ex).

```elixir
def deps do
  [
    {:modest_ex, "~> TBD"}
  ]
end
```

## Target dependencies

- CMake 3.10+
- [Lexbor](https://github.com/lexbor/lexbor) C library

**macOS:**
```bash
brew install lexbor
```

**Ubuntu/Debian:**
```bash
sudo apt-get install liblexbor-dev
```

**From source:**
```bash
git clone https://github.com/lexbor/lexbor.git
cd lexbor && mkdir build && cd build
cmake .. && make && sudo make install
```

## Compile and test
```
mix deps.get
mix compile
mix test
```

## Roadmap

See [CHANGELOG](https://github.com/f34nk/modest_ex/blob/master/CHANGELOG.md).

- [x] Bindings
  - [x] ~~Call as C-Node~~ (removed in 2x)
  - [x] Call via [lexbor_erl](https://github.com/f34nk/lexbor_erl) port
- [x] Tests
  - [x] Feature tests
  - [x] GitHub Actions CI (Ubuntu, macOS)
- [ ] Features
  - [x] Find nodes using a CSS selector
  - [ ] Serialize any string with valid or broken html
  - [x] Get attribute with optional CSS selector
  - [x] Set attribute with optional CSS selector
  - [x] Get text with optional CSS selector
  - [x] Set text with optional CSS selector
  - [x] Remove a node from html
  - [x] Append node to another node
  - [x] Prepend node to another node
  - [x] Insert node before another node
  - [x] Insert node after another node
  - [x] Replace node with another node
  - [ ] Slice html to a subset of nodes
  - [ ] Get position of node in relation to its parent
  - [ ] Wrap node with another node
  - [ ] Streaming of large documents
  - [ ] Pretty print html
  - [ ] Compare two html strings
  - [ ] Transform html string by list of actions
- [ ] ~~Custom CSS selector for pseudo class `:contains(text)`~~ (not supported by Lexbor)
- [x] Scope flag to control serialization (supported to be backwards compatible with Modest)
- [x] List of supported CSS Selectors
- [x] Documentation
- [x] Publish as hex package

## License

ModestEx is under LGPL license. Check the [LICENSE](https://github.com/f34nk/modest_ex/blob/master/LICENSE) file for more details.


## Icon Credit

humble by Eliricon from the Noun Project
