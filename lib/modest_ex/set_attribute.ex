defmodule ModestEx.SetAttribute do
  
  def set_attribute([bin|bins], key, [value|values]) when is_bitstring(key) do
    [set_attribute(bin, key, value)] ++ set_attribute(bins, key, values)
  end

  def set_attribute([bin|bins], key, value) when is_bitstring(key) when is_bitstring(value) do
    [set_attribute(bin, key, value)] ++ set_attribute(bins, key, value)
  end

  def set_attribute([], _, _), do: []

  def set_attribute(bin, key, value) when is_bitstring(bin) when is_bitstring(key) when is_bitstring(value) do
    ModestEx.Safe.Attribute.set_attribute(bin, key, value)
  end

  def set_attribute([bin|bins], selector, key, [value|values]) when is_bitstring(selector) when is_bitstring(key) do
    [set_attribute(bin, selector, key, value)] ++ set_attribute(bins, selector, key, values)
  end

  def set_attribute([bin|bins], selector, key, value) when is_bitstring(selector) when is_bitstring(key) when is_bitstring(value) do
    [set_attribute(bin, selector, key, value)] ++ set_attribute(bins, selector, key, value)
  end

  def set_attribute([], _, _, _), do: []

  def set_attribute(bin, selector, key, value) when is_bitstring(bin) when is_bitstring(selector) when is_bitstring(key) when is_bitstring(value) do
    ModestEx.Safe.Attribute.set_attribute(bin, selector, key, value)
  end

end