defmodule ModestEx.Slice do
  @moduledoc false

  def slice(_, _, start_index, end_index)
      when not is_integer(start_index)
      when not is_integer(end_index) do
    []
  end

  def slice([bin | rest], selector, start_index, end_index) when is_bitstring(selector) do
    slice(bin, selector, start_index, end_index) ++ slice(rest, selector, start_index, end_index)
  end

  def slice([], _, _, _), do: []

  def slice(bin, selector, start_index, end_index)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_integer(start_index)
      when is_integer(end_index) do
    ModestEx.LexborHelper.not_implemented("slice/4")
  end
end
