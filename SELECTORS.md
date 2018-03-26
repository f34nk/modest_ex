## CSS Selectors

The W3C CSS specification contains the [complete set of rules regarding valid CSS selectors](https://www.w3.org/TR/CSS21/selector.html).

| Pattern         | Supported | Description |
|-----------------|-----------| ------------------------------|
| *               | yes | Selects all elements |
| E*              | yes | Selects all elements of type `E` |
| E               | yes | Selects all elements of type `E` |
| E[name\|="value"] | yes | Selects elements that have the specified attribute with a value either equal to a given string or starting with that string followed by a hyphen (-). |
| E[name*="value"]  | yes |Selects elements that have the specified attribute with a value containing a given substring. |
| E[name~="value"]  | yes | Selects elements that have the specified attribute with a value containing a given word, delimited by spaces. |
| E[name$="value"]  | yes | Selects elements that have the specified attribute with a value ending exactly with a given string. The comparison is case sensitive. |
| E[name="value"]  | yes | Selects elements that have the specified attribute with a value exactly equal to a certain value. |
| E[name!="value"]  | **no** | Select elements that either don’t have the specified attribute, or do have the specified attribute but not with a certain value. |
| E[name^="value"]  | yes | Selects elements that have the specified attribute with a value beginning exactly with a given string. |
| :button           | **no** | Selects all button elements and elements of type button. Use selector "button" instead. |
| :checkbox         | **no** | Selects all button elements and elements of type checkbox. Use selector "input[type=checkbox]" instead. |
| :checked        | yes | Matches all elements that are checked or selected. |
| parent > child | yes | Selects all direct child elements specified by "child" of elements specified by "parent". |
| .class | yes | Selects all elements with the given class. |
| :contains(text) | [yes](https://github.com/lexborisov/Modest/pull/42) | Select all elements that contain the specified text. The current W3C CSS specification [left this section intentionally blank](https://www.w3.org/TR/selectors-3/#content-selectors). However, some information can be found [in an old spec from 2001](https://www.w3.org/TR/2001/CR-css3-selectors-20011113/#content-selectors). jQuery also [supports this selector](https://api.jquery.com/contains-selector/). |
| ancestor descendant | yes  | Selects all elements that are descendants of a given ancestor. |
| :disabled | yes  | Selects all elements that are disabled. |
| :empty | yes  | Select all elements that have no children (including text nodes). |
| :enabled | yes  | Selects all elements that are enabled. |
| :eq(n) | **no** | Select the element at index `n` within the matched set. |
| even | yes | Selects even elements, zero-indexed. See also odd. For example: "tr:nth-child(even)" |
| :file |     | Selects all elements of type file. |
| :first-child |  yes   | Selects all elements that are the first child of their parent. |
| :first-of-type | yes    | Selects all elements that are the first among siblings of the same element name. |
| :first |  **no**   | Selects the first matched DOM element. |
| :focus |     | Selects element if it is currently focused. |
| :gt(n) |     | Select all elements at an index greater than index `n` within the matched set. |
| [name] |  yes   | Selects elements that have the specified attribute, with any value. |
| :has() |   yes  | Selects elements which contain at least one element that matches the specified selector. |
| :header |     | Selects all elements that are headers, like h1, h2, h3 and so on. |
| :hidden |  **no**   | Selects all elements that are hidden. Use selector "[hidden]" instead. |
| #id | yes    | Selects a single element with the given id attribute. |
| :image |     | Selects all elements of type image. |
| :input |     | Selects all elements of type input. |
| :lang() |     | Selects all elements of the specified language. |
| :last-child | yes    | Selects all elements that are the last child of their parent. |
| :last-of-type |  yes   | Selects all elements that are the last among siblings of the
same element name. |
| :last |  **no**   | Selects the last matched element. |
| :lt(n) |     | Select all elements at an index less than index `n` within the matched set. |
| [name="value"][name2="value2"] | yes    | Matches elements that match all of the specified attribute filters. |
| selector1,selector2,selectorN | yes    | Selects the combined results of all the specified selectors. |
| prev + next |  yes   | Next Adjacent Selector. Selects all next elements matching "next" that are immediately preceded by a sibling "prev". |
| prev ~ siblings | yes    | Next Siblings Selector. Selects all sibling elements that follow after the "prev" element, have the same parent, and match the filtering "siblings" selector. |
| :not() | yes    | Selects all elements that do not match the given selector. |
| :nth-child() |  yes   | Selects all elements that are the nth-child of their parent. |
| :nth-last-child() | yes    | Selects all elements that are the nth-child of their parent, counting from the last element to the first. |
| :nth-last-of-type() | yes    | Selects all the elements that are the nth-child of their parent in relation to siblings with the same element name, counting from the last element to the first. |
| :nth-of-type() | yes    | Selects all elements that are the nth child of their parent in relation to siblings with the same element name. |
| odd | yes    | Selects odd elements, zero-indexed. See also even. For example: "tr:nth-child(odd) |
| :only-child | yes    | Selects all elements that are the only child of their parent. |
| :only-of-type |  yes   | Selects all elements that have no siblings with the same element name. |
| :parent |  **no**   | Select all elements that have at least one child node (either an element or text). |
| :password |     | Selects all elements of type password. |
| :radio |  **no**   | Selects all elements of type radio. |
| :reset |     | Selects all elements of type reset. |
| :root |     | Selects the element that is the root of the document. |
| :selected | **no**    | Selects all elements that are selected. |
| :submit |     | Selects all elements of type submit. |
| :target |     | Selects the target element indicated by the fragment identifier of the document’s URI. |
| :text | **no**     | Selects all input elements of type text. |
| :visible | **no**     | Selects all elements that are visible. |
| :dir() |       | Select an element based on its directionality as determined by the document language. [See](https://developer.mozilla.org/de/docs/Web/CSS/:dir) |
| :matches() |       | Takes a selector list as its argument, and selects any element that can be selected by one of the selectors in that list. This is useful for writing large selectors in a more compact form. [See](https://developer.mozilla.org/en-US/docs/Web/CSS/:matches) |