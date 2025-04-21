using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimator : MonoBehaviour
{
    //getting animator 
    [SerializeField] private Animator anim;
    [SerializeField] private AudioSource source;
    [SerializeField] private AudioClip[] _footsteps;
    [SerializeField] private ParticleSystem jumpParticles, landParticles, launchParticles;

    bool isPlaying;

    private PlayerMovement player;
    // Start is called before the first frame update
    private void Awake()
    {
        player = GetComponent<PlayerMovement>();
    }
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {




        //check if player is here
        if (player == null) return;
        //triger jump animation, stop land animation

        if (player.jumpThisFrame)
        {
            anim.SetTrigger(JumpKey);
            //anim.ResetTrigger(GroundedKey);
           // jumpParticles.Play();
        }
        //triger land animation, stop jump animation
        if (player.landThisFrame)
        {
            //anim.SetTrigger(GroundedKey);
            anim.ResetTrigger(JumpKey);
            if (!isPlaying)
            {
                isPlaying = true;
                //source.PlayOneShot(_footsteps[Random.Range(0, _footsteps.Length)]);
                //landParticles.Play();
            }
        }
        else
        {
            isPlaying = false;
        }


        //Debug.Log(isPlaying);


    }



    #region Animation Keys
    //private static readonly int GroundedKey = Animator.StringToHash("Grounded");
    //private static readonly int IdleSpeedKey = Animator.StringToHash("IdleSpeed");
    private static readonly int JumpKey = Animator.StringToHash("Jump");
    #endregion
}
