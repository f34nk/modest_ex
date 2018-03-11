defmodule ModestEx.Safe do
  @moduledoc false

  use Application

  app = Mix.Project.config[:app]

  def start(_type, _args) do
    import Supervisor.Spec
    unless Node.alive? do
      Nodex.Distributed.up
    end
    modest_worker = Path.join(:code.priv_dir(unquote(app)), "modest_worker")
    children = [
      worker(Nodex.Cnode, [%{exec_path: modest_worker}, [name: ModestEx.Safe.Cnode]])
    ]
    Supervisor.start_link(children, strategy: :one_for_one, name: ModestEx.Safe.Supervisor)
  end

end

