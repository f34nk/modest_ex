defmodule ModestEx.GetAttribute do
  @moduledoc false

  def get_attribute([bin | bins], key) when is_bitstring(key) do
    get_attribute(bin, key) ++ get_attribute(bins, key)
  end

  def get_attribute([], _), do: []

  def get_attribute(bin, key) when is_bitstring(bin) when is_bitstring(key) do
    ModestEx.Safe.Attribute.get_attribute(bin, key)
  end

  def get_attribute([bin | bins], selector, key)
      when is_bitstring(selector)
      when is_bitstring(key) do
    get_attribute(bin, selector, key) ++ get_attribute(bins, selector, key)
  end

  def get_attribute([], _, _), do: []

  def get_attribute(bin, selector, key)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(key) do
    ModestEx.Safe.Attribute.get_attribute(bin, selector, key)
  end
end
