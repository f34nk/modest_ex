defmodule ModestEx.Slice do
  @moduledoc false
  
  def slice([bin|rest], selector, start_index, end_index) when is_bitstring(selector) do
    slice(bin, selector, start_index, end_index) ++ slice(rest, selector, start_index, end_index)
  end

  def slice([], _, _, _), do: []
  
  def slice(bin, selector, start_index, end_index) when is_bitstring(bin) when is_bitstring(selector) is_integer(start_index) is_integer(end_index) do
    slice(bin, selector, Integer.to_string(start_index), Integer.to_string(end_index))
  end

  def slice(bin, selector, start_index, end_index) when is_bitstring(bin) when is_bitstring(selector) is_bitstring(start_index) is_bitstring(end_index) do
    ModestEx.Safe.Slice.slice(bin, selector, start_index, end_index)
  end
  
end