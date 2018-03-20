defmodule ModestEx.Compare do
  @moduledoc false

  def compare(bin1, bin2) when is_bitstring(bin1) when is_bitstring(bin2) do
    ModestEx.Safe.Compare.compare(bin1, bin2)
  end

end