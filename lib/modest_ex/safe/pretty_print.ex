defmodule ModestEx.Safe.PrettyPrint do
  @moduledoc false
  
  def pretty_print(bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:pretty_print, bin <> "\0"}) do
      {:ok, {:pretty_print, result}} -> result
      _ -> {:error, bin}
    end
  end

end