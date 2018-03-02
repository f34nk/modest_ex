defmodule ModestEx.Safe do
  @moduledoc false

  use Application

  app = Mix.Project.config[:app]

  def start(_type, _args) do
    import Supervisor.Spec
    unless Node.alive? do
      Nodex.Distributed.up
    end
    modest_worker = Path.join(:code.priv_dir(unquote(app)), "modest_client")
    children = [
      worker(Nodex.Cnode, [%{exec_path: modest_worker}, [name: ModestEx.Safe.Cnode]])
    ]
    Supervisor.start_link(children, strategy: :one_for_one, name: ModestEx.Safe.Supervisor)
  end

  # def find(bin, selector, delimiter) do
  #   case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:find, bin <> "\0", selector <> "\0", delimiter <> "\0"}) do
  #     {:ok, {:find, result}} -> result
  #     _ -> {:error, bin}
  #   end
  # end
  
  # #
  # # TODO: Find better solution for String.split
  # # String.split/2 is too slow with large strings
  # # https://github.com/elixir-lang/elixir/issues/6148
  # # 
  # def find(bin, selector) do
  #   delimiter = "|"
  #   case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:find, bin <> "\0", selector <> "\0", delimiter <> "\0"}) do
  #     {:ok, {:find, result}} -> String.split(result, delimiter)
  #     _ -> {:error, bin}
  #   end
  # end

  # def serialize(bin) do
  #   case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:serialize, bin <> "\0"}) do
  #     {:ok, {:serialize, reply}} -> 
  #       case reply do
  #         <<"<-undef>"::utf8>> <> result -> result
  #         _ -> {:error, reply}
  #       end
  #     _ -> {:error, bin}
  #   end
  # end

end

