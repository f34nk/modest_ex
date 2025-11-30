defmodule ModestEx.SetAttribute do
  @moduledoc false

  def set_attribute([bin | bins], selector, key, [value | values])
      when is_bitstring(selector)
      when is_bitstring(key) do
    [set_attribute(bin, selector, key, value)] ++ set_attribute(bins, selector, key, values)
  end

  def set_attribute([bin | bins], selector, key, value)
      when is_bitstring(selector)
      when is_bitstring(key)
      when is_bitstring(value) do
    [set_attribute(bin, selector, key, value)] ++ set_attribute(bins, selector, key, value)
  end

  def set_attribute([], _, _, _), do: []

  def set_attribute(bin, selector, key, value)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(key)
      when is_bitstring(value) do
    # ModestEx.Safe.Attribute.set_attribute(bin, selector, key, value)
    ModestEx.LexborHelper.not_implemented("set_attribute/4")
  end
end
