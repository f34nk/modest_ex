# ModestEx Changelog

## 0.0.8-dev

March 2018

- Added `:scope` flag to applications config. The scope controls the way html is serialized. Default scope is now `:body_children`, which handles fragmented html as fragments. This behaviour is much closer to the common use case.
- Added custom scope to `ModestEx.serialize`, since this function can be used to build a complete html document from an empty string (see [test](https://github.com/f34nk/modest_ex/blob/master/test/modest_ex_serialize_test.exs#L5-L8) for example).
- `ModestEx.split` now returns a single string on lists with one item. That function is only used internally. However, all features return single strings if only a single result is being processed. That's much easier.

## 0.0.7-dev

March 2018

- Feature `ModestEx.insert_before`
- Feature `ModestEx.insert_after`
- Feature `ModestEx.replace`

## 0.0.6-dev

March 2018

- Feature `ModestEx.prepend`

## 0.0.5-dev

March 2018

- Feature `ModestEx.append`

## 0.0.4-dev

March 2018

- Feature `ModestEx.remove`

## 0.0.3-dev

March 2018

- Feature `ModestEx.get_text`
- Feature `ModestEx.set_text`

## 0.0.2-dev

March 2018

- Features can now be piped together `ModestEx.Find(..) |> ModestEx.get_attribute(...)`
- Added hexpm badge for version and counter
- Added travis build badge
- Feature `ModestEx.set_attribute`
- Feature `ModestEx.get_attribute`
- Moved delimiter to `:modest_ex` config. Default delimiter is `"|"`
- Changes success type to `@type success() :: String.t | [String.t]`

## 0.0.1-dev

February 2018

- List of ModestEx features
- Feature `ModestEx.serialize`
- Feature `ModestEx.find` with optional delimiter
- Documentation
- List of supported CSS selectors
- ModestEx icon
- Package test
- C-Node Binding to Modest library
- LGPL license