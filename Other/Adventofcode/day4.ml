open Core

let part1 mat =
  let n = Array.length mat in
  let m = String.length (Array.get mat 0) in
  let goal = "XMAS" in
  let get i j =
    let row = Array.get mat i in
    String.get row j
  in
  let look i j =
    let ans = ref 0 in
    for di = -1 to 1 do
      for dj = -1 to 1 do
        if di = 0 && dj = 0 then ()
        else
          let found =
            String.foldi goal ~init:true ~f:(fun idx acc c ->
                let i = i + (idx * di) in
                let j = j + (idx * dj) in
                if
                  i < 0 || j < 0 || i >= n || j >= m
                  || not (Char.equal c (get i j))
                then false
                else acc)
          in
          if found then ans := !ans + 1 else ()
      done
    done;
    !ans
  in
  let ans = ref 0 in
  for i = 0 to n - 1 do
    for j = 0 to m - 1 do
      ans := !ans + look i j
    done
  done;
  !ans

let part2 mat =
  let get i j =
    let row = Array.get mat i in
    String.get row j
  in
  let ans = ref 0 in
  for i = 1 to Array.length mat - 2 do
    for j = 1 to String.length (Array.get mat i) - 2 do
      if Char.equal (get i j) 'A' then
        let d1 =
          Char.to_string (get (i - 1) (j - 1))
          ^ Char.to_string (get (i + 1) (j + 1))
          |> String.to_array
          |> Array.sorted_copy ~compare:Char.compare
          |> String.of_array
        in
        let d2 =
          Char.to_string (get (i + 1) (j - 1))
          ^ Char.to_string (get (i - 1) (j + 1))
          |> String.to_array
          |> Array.sorted_copy ~compare:Char.compare
          |> String.of_array
        in
        if String.equal d1 "MS" && String.equal d1 d2 then ans := !ans + 1
        else ()
      else ()
    done
  done;
  !ans

let solve = function `Part1 -> part1 | `Part2 -> part2

let main () =
  let input = In_channel.input_all Stdio.stdin in
  let mat = String.split ~on:'\n' input |> Array.of_list in
  print_endline (Int.to_string (solve `Part1 mat))
