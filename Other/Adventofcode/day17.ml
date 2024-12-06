open Core

module Program = struct
  type t = {
    mutable ra : int;
    mutable rb : int;
    mutable rc : int;
    mutable instruction_pointer : int;
    mutable output : int list;
    program : int array;
  }
  [@@deriving sexp]

  let create (ra, rb, rc) program =
    { ra; rb; rc; instruction_pointer = 0; output = []; program }

  let combo t = function
    | (0 | 1 | 2 | 3) as combo -> combo
    | 4 -> t.ra
    | 5 -> t.rb
    | 6 -> t.rc
    | _ -> failwith "Invalid combo value"

  let literal = Fn.id

  let adv_value t operand =
    let combo_value = combo t operand in
    let numerator = t.ra in
    let denominator = 1 lsl combo_value in
    numerator / denominator

  (* Start of instructions *)

  let adv t operand = t.ra <- adv_value t operand

  let bxl t operand =
    let literal_value = literal operand in
    t.rb <- t.rb lxor literal_value

  let bst t operand =
    let combo_value = combo t operand in
    t.rb <- combo_value mod 8

  let jnz t operand =
    let literal_value = literal operand in
    if not (t.ra = 0) then t.instruction_pointer <- literal_value - 2

  let bxc t _operand = t.rb <- t.rb lxor t.rc

  let out t operand =
    let combo_value = combo t operand in
    t.output <- (combo_value mod 8) :: t.output

  let bdv t operand = t.rb <- adv_value t operand
  let cdv t operand = t.rc <- adv_value t operand

  (* End of instructions *)

  let all_instructions = [| adv; bxl; bst; jnz; bxc; out; bdv; cdv |]

  let dispatch ?(should_continue = fun _t -> true) t =
    while t.instruction_pointer < Array.length t.program && should_continue t do
      let instruction = Array.get t.program t.instruction_pointer in
      let f = Array.get all_instructions instruction in
      let operand = Array.get t.program (t.instruction_pointer + 1) in
      f t operand;
      t.instruction_pointer <- t.instruction_pointer + 2
    done
end

let part1 program =
  Program.dispatch program;
  program.output |> List.rev

let part2 program =
  (* Assumes: 
  - Program only contain a single jump at the end and jumps to 0.
  - `A` only is modified with A = A / 8 in each step
  - It outputs exactly one number in each step
  - The output in each only depends on A in each step *)
  let program = program.Program.program in
  let rec find ~acc i =
    if i < 0 then Some acc
    else
      (* Decide on the 3 bits on the ith iteration *)
      let found = ref None in
      for msc = 0 to 7 do
        if Option.is_none !found then
          let ra = (acc lsl 3) + msc in
          let output =
            let program = Program.create (ra, 0, 0) program in
            Program.dispatch program ~should_continue:(fun t ->
                not (Array.get t.program t.instruction_pointer = 3));
            List.hd_exn program.output
          in
          if output = Array.get program i then found := find ~acc:ra (i - 1)
      done;
      !found
  in
  [ find ~acc:0 (Array.length program - 1) |> Option.value_exn ]

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let lines = String.split input ~on:'\n' in
  let registers, program =
    match lines with
    | [ ra; rb; rc; ""; p ] ->
        let register_value r c =
          String.chop_prefix_exn r ~prefix:("Register " ^ c ^ ": ")
          |> Int.of_string
        in
        let ra = register_value ra "A" in
        let rb = register_value rb "B" in
        let rc = register_value rc "C" in
        let p =
          String.chop_prefix_exn p ~prefix:"Program: "
          |> String.split ~on:',' |> List.map ~f:Int.of_string |> List.to_array
        in
        ((ra, rb, rc), p)
    | _ -> failwith "Invalid input"
  in
  let program = Program.create registers program in
  let ans = solve part program in
  print_s
    [%sexp
      (ans |> List.map ~f:Int.to_string |> String.concat ~sep:"," : string)]

let%expect_test _ =
  let input =
    {|
Register A: 729
Register B: 0
Register C: 0

Program: 0,1,5,4,3,0
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 4,6,3,5,6,3,5,2,1,0 |}]

let%expect_test _ =
  let input =
    {|
Register A: 2024
Register B: 0
Register C: 0

Program: 0,3,5,4,3,0
|}
  in
  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 117440 |}]

let%expect_test _ =
  let input =
    {|
Register A: 18427963
Register B: 0
Register C: 0

Program: 2,4,1,1,7,5,0,3,4,3,1,6,5,5,3,0
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 2,0,7,3,0,3,1,3,7 |}];
  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 247839539763386 |}]
