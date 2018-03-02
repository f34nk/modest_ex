defmodule ModestEx.Safe.Find do
  @moduledoc false
  
  def find(bin, selector) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:find, bin <> "\0", selector <> "\0", ModestEx.delimiter() <> "\0"}) do
      {:ok, {:find, result}} -> ModestEx.split(result)
      _ -> {:error, bin}
    end
  end
  
end