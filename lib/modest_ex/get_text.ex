defmodule ModestEx.GetText do
  @moduledoc false

  def get_text([bin | bins]) do
    get_text(bin) ++ get_text(bins)
  end

  def get_text([]), do: []

  def get_text(bin) when is_bitstring(bin) do
    ModestEx.Safe.Text.get_text(bin)
  end

  def get_text([bin | bins], selector) when is_bitstring(selector) do
    get_text(bin, selector) ++ get_text(bins, selector)
  end

  def get_text([], _), do: []

  def get_text(bin, selector) when is_bitstring(bin) when is_bitstring(selector) do
    ModestEx.Safe.Text.get_text(bin, selector)
  end
end
